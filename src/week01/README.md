
# Week 1 — 数据结构课程实验与练习

本目录包含第 1 周的若干练习代码、数据和一个用于绘制实验结果的 Jupyter Notebook。

## 目录结构（主要文件）

- `DS2025_32_2.cpp` — 生成 n 个布尔变量的所有组合并按行输出（示例程序）。
- `DS2025_33_14.cpp` — 递归打印集合的幂集（Powerset）。
- `DS2025_69_3.cpp` — 计算程序段中各语句执行频度的示例程序。
- `DS2025_69_4.cpp` / `DS2025_69_4.md` — 两段伪代码的步数统计与验证（代码 + 说明）。
- `DS2025_69_10.cpp` / `DS2025_69_10.ipynb` — 对二分查找的运行时间进行实验并把结果写入 `data/runtime.csv`，同时包含一个 Notebook 用于读取并绘图。
- `data/runtime.csv` — 由 `DS2025_69_10.cpp` 生成的实验数据（如果已经生成的话）。

## 快速指南 — 编译与运行（Windows / PowerShell）

推荐使用 Visual Studio 的 `cl.exe`（已有 VS 环境）或者安装了 MinGW / MSYS2 的 `g++`。本仓库也包含了一个 VS Code 任务（见工作区任务）用于直接构建当前文件。

1) 使用 VS Code 内置任务（推荐）

	- 打开 VS Code，切换到 `src/week1` 文件夹并打开要运行的源文件。
	- 运行菜单 -> 运行任务（Run Task）-> 选择 “C/C++: cl.exe 生成活动文件”。该任务会将可执行文件输出到源文件所在目录下的 `build\` 子目录，例如：

	  `d:\...\src\week1\build\DS2025_69_10.exe`

2) 手动使用 `cl.exe`（PowerShell）

	- 在 PowerShell 中切换到 `src/week1`：

	  ```powershell
	  cd d:\陈彦明文档\programming\DataStructureClass\src\week1
	  cl.exe /Zi /EHsc /nologo /Fe:build\DS2025_69_10.exe /Fo:build\ DS2025_69_10.cpp
	  ```

	- 或者使用 `g++`（如果你安装了）：

	  ```powershell
	  g++ -O2 -std=c++17 DS2025_69_10.cpp -o build\DS2025_69_10.exe
	  ```

3) 运行生成的可执行文件

	- 可执行文件默认会把 `data/runtime.csv` 写到当前工作目录下的 `data` 子目录（即 `src/week1/data/runtime.csv`）。在 PowerShell 中运行：

	  ```powershell
	  .\build\DS2025_69_10.exe
	  ```

	- 程序运行完成后会在 `data/runtime.csv` 中产生或更新 `n,average_time(ns)` 的表格。

## 可视化（Jupyter Notebook）

- Notebook 文件：`DS2025_69_10.ipynb`，已附带绘图代码（使用 pandas + matplotlib + seaborn）。

1) 建议使用 Python 3.8+ 的环境，并安装下列依赖：

	```powershell
	python -m pip install --upgrade pip
	python -m pip install pandas matplotlib seaborn numpy jupyterlab
	```

2) 打开 Notebook

	- 在 VS Code 中直接打开 `DS2025_69_10.ipynb` 并依次运行代码单元，或者在命令行启动 JupyterLab：

	  ```powershell
	  jupyter lab
	  ```

3) 注意事项

	- Notebook 的绘图单元默认会读取 `data/runtime.csv`，请先运行 C++ 程序生成该文件，或者手动把实验数据放到同一路径下。
	- Notebook 中通过简单的 O(log n) 参考曲线与实测数据比较来观察趋势。

## 实验与验证提示

- 对小的 n 值（如 2..100）实验可能会受到计时器分辨率和系统负载影响。代码里通过重复多次搜索并取平均来减小噪声；如果你需要更稳定的测量，可增加 `repetitions` 或在更安静的系统上运行。
- `DS2025_69_10.cpp` 使用高分辨率计时器（std::chrono::high_resolution_clock），并把平均时间以纳秒为单位写入 CSV。

## 贡献与问题

如果你希望改进测量方式（例如使用 CPU 性能计数器、固定 CPU 亲和性或改进随机化策略），欢迎提交 issue 或 pull request。

----

最后更新：请在运行前确认你的 C++ 编译器与 Python 环境设置正确。

