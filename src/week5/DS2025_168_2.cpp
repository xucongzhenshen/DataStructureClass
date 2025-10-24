#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include <string>
#include <sstream>

// Airport landing/takeoff simulation (Landweber project)
// Implements: 4 landing holding patterns (two per runway 1 and 2),
// 3 takeoff queues (one per runway). Uses odd IDs for landings and
// even IDs for takeoffs. Simple random input generator is used by default.

class AirportSimulation
{
public:
    AirportSimulation(int totalTime, int reportPeriod = 5)
        : totalTimeUnits(totalTime), reportPeriod(reportPeriod) {}
    void runSimulation();

private:
    struct Plane
    {
        int id;
        int fuelTime;    // remaining flying time (for landing planes)
        int arrivalTime; // time unit when plane entered queue
        Plane(int i = 0, int f = 0, int a = 0) : id(i), fuelTime(f), arrivalTime(a) {}
    };

    // Use deques for FIFO queues and to allow iteration (for decrementing fuel)
    std::deque<Plane> lq1a, lq1b;    // landing queues for runway 1
    std::deque<Plane> lq2a, lq2b;    // landing queues for runway 2
    std::deque<Plane> tq1, tq2, tq3; // takeoff queues for runways 1,2,3

    int nextLandingId = 1; // odd integers for landing
    int nextTakeoffId = 2; // even integers for takeoff

    int totalTimeUnits;
    int reportPeriod;

    // Statistics
    long long landedCount = 0;
    long long totalLandingWait = 0; // sum of waiting times for landed planes
    long long takeoffCount = 0;
    long long totalTakeoffWait = 0;            // sum of waiting times for taken-off planes
    long long totalRemainingFuelOnLanding = 0; // sum of remaining fuelTime at landing
    long long landedWithNoFuel = 0;            // number of planes that landed with fuelTime <= 0

    // Random generator
    std::mt19937 rng{std::random_device{}()};

    // Helpers
    void enqueueLanding(int count, int currentTime);
    void enqueueTakeoff(int count, int currentTime);
    void decrementLandingFuel();
    void serviceRunways(int currentTime);
    void printQueues(int currentTime) const;
    int totalLandingQueueSizeForRunway1() const { return (int)lq1a.size() + (int)lq1b.size(); }
    int totalLandingQueueSizeForRunway2() const { return (int)lq2a.size() + (int)lq2b.size(); }
    int totalTakeoffQueueSize() const { return (int)tq1.size() + (int)tq2.size() + (int)tq3.size(); }
    std::string planeSummary(const Plane &p) const
    {
        std::ostringstream oss;
        oss << "[id=" << p.id << ",f=" << p.fuelTime << ",a=" << p.arrivalTime << "]";
        return oss.str();
    }
};

// Implementation
void AirportSimulation::enqueueLanding(int count, int currentTime)
{
    std::uniform_int_distribution<int> fuelDist(1, 10);
    for (int i = 0; i < count; ++i)
    {
        Plane p(nextLandingId, fuelDist(rng), currentTime);
        nextLandingId += 2;
        // place into the landing queue with smallest size (across all 4 queues)
        auto chooseMin = [&](std::deque<Plane> &a, std::deque<Plane> &b, std::deque<Plane> &c, std::deque<Plane> &d) -> std::deque<Plane> *
        {
            std::deque<Plane> *arr[4] = {&a, &b, &c, &d};
            int minIdx = 0;
            for (int j = 1; j < 4; ++j)
                if (arr[j]->size() < arr[minIdx]->size())
                    minIdx = j;
            return arr[minIdx];
        };
        std::deque<Plane> *q = chooseMin(lq1a, lq1b, lq2a, lq2b);
        q->push_back(p);
    }
}

void AirportSimulation::enqueueTakeoff(int count, int currentTime)
{
    for (int i = 0; i < count; ++i)
    {
        Plane p(nextTakeoffId, 0, currentTime);
        nextTakeoffId += 2;
        // choose smallest takeoff queue among tq1,tq2,tq3
        std::deque<Plane> *arr[3] = {&tq1, &tq2, &tq3};
        int minIdx = 0;
        for (int j = 1; j < 3; ++j)
            if (arr[j]->size() < arr[minIdx]->size())
                minIdx = j;
        arr[minIdx]->push_back(p);
    }
}

void AirportSimulation::decrementLandingFuel()
{
    auto dec = [](std::deque<Plane> &q)
    {
        for (auto &p : q)
            --p.fuelTime;
    };
    dec(lq1a);
    dec(lq1b);
    dec(lq2a);
    dec(lq2b);
}

void AirportSimulation::serviceRunways(int currentTime)
{
    // Determine emergency candidates: check front of each landing queue for fuelTime <= 0
    struct Candidate
    {
        Plane p;
        int which; /* 0..3 for landing queues idx */
    };
    std::vector<Candidate> emergencies;
    auto checkFront = [&](std::deque<Plane> &q, int idx)
    {
        if (!q.empty() && q.front().fuelTime <= 0)
            emergencies.push_back({q.front(), idx});
    };
    checkFront(lq1a, 0);
    checkFront(lq1b, 1);
    checkFront(lq2a, 2);
    checkFront(lq2b, 3);

    // If emergencies exist, sort by arrival time and service up to 3 earliest
    if (!emergencies.empty())
    {
        std::sort(emergencies.begin(), emergencies.end(), [](const Candidate &a, const Candidate &b)
                  { return a.p.arrivalTime < b.p.arrivalTime; });
        int toService = std::min((size_t)3, emergencies.size());
        // Service these (assign to runways 3 first if only one emergency; otherwise use all runways)
        for (int i = 0; i < toService; ++i)
        {
            Candidate c = emergencies[i];
            // remove the plane from the corresponding queue's front and record stats
            std::deque<Plane> *qptr = nullptr;
            if (c.which == 0)
                qptr = &lq1a;
            if (c.which == 1)
                qptr = &lq1b;
            if (c.which == 2)
                qptr = &lq2a;
            if (c.which == 3)
                qptr = &lq2b;
            if (qptr && !qptr->empty())
            {
                Plane p = qptr->front();
                qptr->pop_front();
                long long wait = currentTime - p.arrivalTime;
                ++landedCount;
                totalLandingWait += wait;
                totalRemainingFuelOnLanding += p.fuelTime;
                if (p.fuelTime <= 0)
                    ++landedWithNoFuel;
                std::cout << "Time " << currentTime << ": EMERGENCY LANDING plane " << p.id << " (wait=" << wait << ")\n";
            }
        }
        // any remaining runways (if <3 emergencies) can process non-emergencies below
    }

    // Now service remaining runways up to total of 3 services per time unit.
    // Count how many services already done by emergencies.
    int emergencyCount = std::min(3, (int)emergencies.size());
    int remainingSlots = 3 - emergencyCount;
    // For simplicity: assign priority to runway3 for takeoff (if no leftover emergency),
    // runways1 and 2 try to land if landing queues for that runway are non-empty; otherwise do takeoff.

    auto tryServiceLandingForRunway = [&](std::deque<Plane> &qa, std::deque<Plane> &qb, std::deque<Plane> &tq, int &slots)
    {
        if (slots <= 0)
            return;
        // prefer landing if any
        if (!qa.empty() || !qb.empty())
        {
            // pick the queue (qa or qb) whose front arrived earlier
            bool useA = false;
            if (!qa.empty() && qb.empty())
                useA = true;
            else if (qa.empty() && !qb.empty())
                useA = false;
            else
                useA = (qa.front().arrivalTime <= qb.front().arrivalTime);
            Plane p = useA ? qa.front() : qb.front();
            if (useA)
                qa.pop_front();
            else
                qb.pop_front();
            long long wait = /*currentTime*/ 0; // will compute outside since currentTime not captured here
            // We'll compute wait and stats after returning control; instead, recompute here via lambda capture
        }
    };

    // To keep code straightforward, explicitly handle remaining slots and runways:
    for (int r = 1; r <= 3 && remainingSlots > 0; ++r)
    {
        if (r == 3)
        {
            // runway 3: if there was exactly 1 emergency it should have taken runway 3
            // but we've already printed emergency handling. If slot remains, do takeoff from tq3
            if (!tq3.empty())
            {
                Plane p = tq3.front();
                tq3.pop_front();
                long long wait = currentTime - p.arrivalTime;
                ++takeoffCount;
                totalTakeoffWait += wait;
                std::cout << "Time " << currentTime << ": TAKEOFF runway3 plane " << p.id << " (wait=" << wait << ")\n";
                --remainingSlots;
            }
        }
        else if (r == 1)
        {
            // runway 1: prefer landing from lq1a/lq1b; else takeoff from tq1
            if (!lq1a.empty() || !lq1b.empty())
            {
                bool useA = false;
                if (!lq1a.empty() && lq1b.empty())
                    useA = true;
                else if (lq1a.empty() && !lq1b.empty())
                    useA = false;
                else
                    useA = (lq1a.front().arrivalTime <= lq1b.front().arrivalTime);
                Plane p = useA ? lq1a.front() : lq1b.front();
                if (useA)
                    lq1a.pop_front();
                else
                    lq1b.pop_front();
                long long wait = currentTime - p.arrivalTime;
                ++landedCount;
                totalLandingWait += wait;
                totalRemainingFuelOnLanding += p.fuelTime;
                if (p.fuelTime <= 0)
                    ++landedWithNoFuel;
                std::cout << "Time " << currentTime << ": LANDING runway1 plane " << p.id << " (wait=" << wait << ")\n";
                --remainingSlots;
            }
            else if (!tq1.empty())
            {
                Plane p = tq1.front();
                tq1.pop_front();
                long long wait = currentTime - p.arrivalTime;
                ++takeoffCount;
                totalTakeoffWait += wait;
                std::cout << "Time " << currentTime << ": TAKEOFF runway1 plane " << p.id << " (wait=" << wait << ")\n";
                --remainingSlots;
            }
        }
        else if (r == 2)
        {
            // runway 2: prefer landing from lq2a/lq2b; else takeoff from tq2
            if (!lq2a.empty() || !lq2b.empty())
            {
                bool useA = false;
                if (!lq2a.empty() && lq2b.empty())
                    useA = true;
                else if (lq2a.empty() && !lq2b.empty())
                    useA = false;
                else
                    useA = (lq2a.front().arrivalTime <= lq2b.front().arrivalTime);
                Plane p = useA ? lq2a.front() : lq2b.front();
                if (useA)
                    lq2a.pop_front();
                else
                    lq2b.pop_front();
                long long wait = currentTime - p.arrivalTime;
                ++landedCount;
                totalLandingWait += wait;
                totalRemainingFuelOnLanding += p.fuelTime;
                if (p.fuelTime <= 0)
                    ++landedWithNoFuel;
                std::cout << "Time " << currentTime << ": LANDING runway2 plane " << p.id << " (wait=" << wait << ")\n";
                --remainingSlots;
            }
            else if (!tq2.empty())
            {
                Plane p = tq2.front();
                tq2.pop_front();
                long long wait = currentTime - p.arrivalTime;
                ++takeoffCount;
                totalTakeoffWait += wait;
                std::cout << "Time " << currentTime << ": TAKEOFF runway2 plane " << p.id << " (wait=" << wait << ")\n";
                --remainingSlots;
            }
        }
    }
}

void AirportSimulation::printQueues(int currentTime) const
{
    auto printDeque = [&](const std::deque<Plane> &q)
    {
        std::ostringstream oss;
        for (const auto &p : q)
        {
            oss << " " << p.id << "(f=" << p.fuelTime << ")";
        }
        return oss.str();
    };
    std::cout << "\n--- Status at time " << currentTime << " ---\n";
    std::cout << "Runway1 landing queues: A:" << printDeque(lq1a) << "  B:" << printDeque(lq1b) << "\n";
    std::cout << "Runway2 landing queues: A:" << printDeque(lq2a) << "  B:" << printDeque(lq2b) << "\n";
    std::cout << "Takeoff queues: 1:" << printDeque(tq1) << " 2:" << printDeque(tq2) << " 3:" << printDeque(tq3) << "\n";
    std::cout << "Stats so far: landed=" << landedCount << " takenOff=" << takeoffCount << "\n";
    if (takeoffCount > 0)
        std::cout << "  avg takeoff wait=" << (double)totalTakeoffWait / takeoffCount << "\n";
    if (landedCount > 0)
        std::cout << "  avg landing wait=" << (double)totalLandingWait / landedCount << "\n";
    if (landedCount > 0)
        std::cout << "  avg remaining flying time on landing=" << (double)totalRemainingFuelOnLanding / landedCount << "\n";
    std::cout << "  landed with no fuel reserve=" << landedWithNoFuel << "\n";
}

void AirportSimulation::runSimulation()
{
    std::uniform_int_distribution<int> arrivalsDist(0, 3);
    for (int t = 1; t <= totalTimeUnits; ++t)
    {
        int takeoffArrivals = arrivalsDist(rng);
        int landingArrivals = arrivalsDist(rng);
        // Enqueue arrivals (arrivals happen before servicing)
        enqueueTakeoff(takeoffArrivals, t);
        enqueueLanding(landingArrivals, t);

        // Decrement remaining flying times for landing planes (time passes)
        decrementLandingFuel();

        // Service runways (up to 3 planes)
        serviceRunways(t);

        // Periodic reporting
        if (t % reportPeriod == 0 || t == totalTimeUnits)
            printQueues(t);
    }

    // Final summary
    std::cout << "\n=== Final Summary ===\n";
    std::cout << "Total planes landed: " << landedCount << "\n";
    if (landedCount)
        std::cout << "  Avg landing wait: " << (double)totalLandingWait / landedCount << "\n";
    std::cout << "Total planes taken off: " << takeoffCount << "\n";
    if (takeoffCount)
        std::cout << "  Avg takeoff wait: " << (double)totalTakeoffWait / takeoffCount << "\n";
    if (landedCount)
        std::cout << "Avg remaining flying time on landing: " << (double)totalRemainingFuelOnLanding / landedCount << "\n";
    std::cout << "Planes landed with no fuel reserve: " << landedWithNoFuel << "\n";
}

// Simple main to run the simulation
int main()
{
    int timeUnits = 30;
    int reportPeriod = 5;
    std::cout << "Airport simulation (random arrivals). Running for " << timeUnits << " time units.\n";
    AirportSimulation sim(timeUnits, reportPeriod);
    sim.runSimulation();
    return 0;
}