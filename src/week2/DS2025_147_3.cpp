/*To the class Queue, add a function to split a queue into two queues.The
first queue is to contain every other element beginning with the first;
the second queue contains the remaining elements.The relative order of queue
elements is unchanged.What is the complexity of your function?
*/
void splitQueue(Queue &q1, Queue &q2)
{
    Queue temp;
    int count = 0;

    while (!isEmpty())
    {
        if (count % 2 == 0)
        {
            enqueue(temp, dequeue());
        }
        else
        {
            enqueue(q2, dequeue());
        }
        count++;
    }

    // Restore the original queue
    while (!isEmpty(temp))
    {
        enqueue(q1, dequeue(temp));
    }
}

/*
Complexity analysis:

The function iterates through the original queue once,
performing O(1) operations (enqueue and dequeue) for each
element.

Therefore, the time complexity is O(n), where n
is the number of elements in the original queue.

The space complexity is also O(n) in the worst case,
 as we may need to store all elements in the two new queues.
 */