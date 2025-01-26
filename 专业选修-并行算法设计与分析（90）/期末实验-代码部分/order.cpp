#include "fstream"
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct node
{
    int row;
    int col;
    double value;
    node(int r, int c, double v)
    {
        this->row = r;
        this->col = c;
        this->value = v;
    }
};

struct cmp
{
    bool operator()(node a, node b)
    {
        if (a.row > b.row)
            return 1;
        else if (a.row == b.row && a.col > b.col)
            return 1;
        return 0;
    }
};

void process(string filename)
{
    string file_e = filename + ".mtx";
    const char *file = file_e.c_str();
    FILE *f = fopen(file, "r");
    if (f == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", file);
        exit(1);
    }

    // 跳过第一行的说明信息
    char line[256];
    if (fgets(line, sizeof(line), f) == NULL)
    {
        fprintf(stderr, "Error reading file header\n");
        fclose(f);
        exit(1);
    }

    // 读取矩阵的基本信息
    int n_rows, n_cols, n_nonzero;
    if (fscanf(f, "%d %d %d", &n_rows, &n_cols, &n_nonzero) != 3)
    {
        fprintf(stderr, "Error reading matrix dimensions\n");
        fclose(f);
        exit(1);
    }
    // cout << n_rows << " " << n_cols << " " << n_nonzero;

    std::priority_queue<node, std::vector<node>, cmp> q;

    for (int i = 0; i < n_nonzero; i++)
    {
        int r, c;
        double v;
        if (fscanf(f, "%d %d %le", &r, &c, &v) != 3)
        {
            fprintf(stderr, "Error reading matrix element\n");
            fclose(f);
            exit(1);
        }
        node new_node(r, c, v);
        q.push(new_node);
    }

    // 将队列元素复制到vector
    std::vector<node> vec;
    while (!q.empty())
    {
        vec.push_back(q.top());
        q.pop();
    }

    cout << "start to output" << endl;

    // 输出
    string outfile = filename + "_line.mtx";
    std::ofstream outFile(outfile);
    if (outFile.is_open())
    {
        // 将输出写入文件
        outFile << line;
        outFile << n_rows << " " << n_cols << " " << n_nonzero << endl;
        // 反向遍历vector，因为复制到vector中的元素顺序是逆序的
        for (auto it = vec.begin(); it != vec.end(); ++it)
        {
            outFile << std::fixed << it->row << " " << it->col << " ";
            outFile << std::scientific << std::setprecision(13) << it->value << std::endl;
        }
        outFile << endl;
        // 关闭文件
        outFile.close();
        std::cout << "Output written to output." << std::endl;
    }
    else
    {
        std::cerr << "Unable to open output file." << std::endl;
        return;
    }
    fclose(f);
    return;
}

int main(int argc, char *argv[])
{
    // 读取参数，确定处理目标
    string target;
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <matrix name>\n";
        return 1;
    }
    try
    {
        target = argv[1];
        std::cout << "process target : " << target << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: " << e.what() << " - Invalid argument: " << argv[1] << std::endl;
        return 1;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Error: " << e.what() << " - Argument " << argv[1] << " is out of range" << std::endl;
        return 1;
    }

    string filename = target;
    process(filename);
    return 0;
}
