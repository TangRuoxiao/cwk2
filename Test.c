#include "CuTest.c"
#define CELL 40
int state[50][50];
int next[50][50];
int col = 0, row = 0;
int read(char *filename)
{
    FILE *file;
    file = fopen(filename, "r");
    //check if fault
    if (file == NULL||filename==NULL)
    {
        return -1;
    }
    //read
    fscanf(file, "%d%d\n", &col, &row);
    char c;
    for (int i = 0; i < col; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            c = fgetc(file);
            if (c == '0')
            {
                state[i][j] = 0;
            }
            else if (c == '1')
            {
                state[i][j] = 1;
            }
            else if (c == '\n')
            {
                i--;
                break;
            }
        }
    }
    fclose(file);
    return 0;
}
//the module to write the data
int write(char *filename)
{
    FILE *file = fopen(filename, "w+");
    //write
    if (filename==NULL)
    {
        return -1;
    }
    fprintf(file, "%d %d\n", col, row);
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            if (state[i][j]==1)
            {
                fputc('1',file);
            }else
            {
                fputc('0',file);
            }
        }
        fputc('\n',file);
    }
    return 0;
}
void test_read(CuTest *cuTest)
{
    CuAssert(cuTest, "\r\ntest not pass", 0==read("init.txt"));
}
void test_readwrongfile(CuTest *cuTest)
{
    CuAssert(cuTest, "\r\ntest not pass", -1==read("wrong"));
}
void test_readnofile(CuTest *cuTest)
{
    CuAssert(cuTest, "\r\ntest not pass", -1 == read(NULL));
}
void test_write(CuTest *cuTest)
{
    CuAssert(cuTest, "\r\ntest not pass", 0==write("final.txt"));
}
void test_writenofile(CuTest *cuTest)
{
    CuAssert(cuTest, "\r\ntest not pass", -1==write(NULL));
}
int main(void)
{
    CuString *output = CuStringNew(); //定义用于存储测试信息的宁符串
    CuSuite *suite = CuSuiteNew();
    //新建测试套件
    SUITE_ADD_TEST(suite, test_read);
    SUITE_ADD_TEST(suite, test_readnofile);
    SUITE_ADD_TEST(suite, test_readwrongfile);
    SUITE_ADD_TEST(suite, test_write);
    SUITE_ADD_TEST(suite, test_writenofile);
    CuSuiteRun(suite);
    //运行测武套件
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
    //打印测试结果
}