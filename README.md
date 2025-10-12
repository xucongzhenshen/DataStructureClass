
# DataStructureClass

这是用于保存数据结构课程（练习与实验代码）的个人代码仓库，按周组织样例程序、实验和笔记。该仓库包含若干 C++ 源文件、一个用于绘图的 Jupyter Notebook、以及实验数据文件。

## 目标

- 收集和记录课堂练习代码与小实验。 
- 提供可重复运行的实验（例如：二分查找运行时间测量）。
- 使用轻量笔记（Markdown / Notebook）记录分析与结果展示。

## 仓库结构（概要）

- `src/` — 源代码与 Notebook，按周分目录（例如 `week1/`, `week2/`）。
	- `src/week1/` 包含布尔组合、幂集、步数统计、二分查找实验与绘图 Notebook 等示例。
	- 每个 `weekX` 子目录可能包含 `build/`、`data/` 等辅助目录。

## 常见文件说明（以 week1 为例）

- `DS2025_32_2.cpp` — 生成 n 个布尔变量的所有组合并打印。
- `DS2025_33_14.cpp` — 使用递归打印集合的幂集。
- `DS2025_69_3.cpp` — 统计嵌套循环中语句执行频度的示例。
- `DS2025_69_4.cpp` / `DS2025_69_4.md` — 另一个步数统计的实现与分析说明。
- `DS2025_69_10.cpp` — 二分查找运行时间实验（将输出写入 `src/week1/data/runtime.csv`）。
- `DS2025_69_10.ipynb` — Notebook：读取 `data/runtime.csv` 并绘制运行时间对比图。

## 快速开始（Windows / PowerShell）

1) 进入源码目录（以第 1 周为例）：

```powershell
cd d:\..\programming\DataStructureClass\src\week1
```

2) 使用 Visual Studio 的 `cl.exe`（或 VS Code 任务）构建单个源文件：

```powershell
cl.exe /Zi /EHsc /nologo /Fe:build\DS2025_69_10.exe /Fo:build\ DS2025_69_10.cpp
# 或者使用仓库中的 VS Code 任务（Run Task -> C/C++: cl.exe 生成活动文件）
```

3) 使用 `g++`（若已安装）构建：

```powershell
g++ -O2 -std=c++17 DS2025_69_10.cpp -o build\DS2025_69_10.exe
```

4) 运行生成的可执行文件生成实验数据：

```powershell
.\build\DS2025_69_10.exe
```

生成的 `data/runtime.csv` 将包含两列：`n,average_time(ns)`。

## 使用 Notebook 可视化

推荐 Python 3.8+，安装依赖：

```powershell
python -m pip install --upgrade pip
python -m pip install pandas matplotlib seaborn numpy jupyterlab
```

然后在仓库根或 `src/week1` 中启动 JupyterLab 或在 VS Code 中打开 Notebook：

```powershell
jupyter lab
```

打开 `src/week1/DS2025_69_10.ipynb` 并运行单元，即可看到运行时间与 O(log n) 参考曲线的比较。

## 实验建议与注意事项

- 计时非常容易受到系统负载、CPU 频率调整与计时器分辨率影响。建议在静止负载下运行、关闭不必要的后台程序，以及提高 `repetitions` 来减小噪声。
- 若需更精确的基准，可考虑使用 CPU 性能计数器（如 RDTSCP）或固定 CPU 亲和性。

## 贡献与改进

欢迎在此仓库中提交改进建议与 Pull Request。你可以：

- 添加更多练习实现或将函数改写为可复用的库组件。
- 为每个实验添加单元测试或更完善的基准脚本。
- 将 Notebook 扩展为自动分析与报告生成脚本。

----

最后更新：2025-10-12

