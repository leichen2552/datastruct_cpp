#include <iostream>
#include <cstring>
#include "DTstring.h"

using namespace std;
using namespace DTLib;

int* make_pmt(const char* p) //O(m)
{
    int len = strlen(p);
    int* ret = static_cast<int*>(malloc(sizeof(int) * len));

    if( ret != NULL )
    {
        int ll = 0;

        ret[0] = 0;

        for(int i=1; i<len; i++)
        {
            while( (ll > 0) && (p[ll] != p[i]) )//直到ll等于0就跳出循环
            {
                ll = ret[ll-1];
            }

            if( p[ll] == p[i] )//最理想的情况，如果第一个字符等于最后一个字符，那么ll直接自加1
            {
                ll++;
            }

            ret[i] = ll;//那么这个时候，ll值存在部分匹配表里面
        }
    }

    return ret;
}

int kmp(const char* s, const char* p) //O(n)，比朴素算法O(m*n)强很多
{
    int ret = -1;
    int sl = strlen(s);
    int pl = strlen(p);
    int* pmt = make_pmt(p);


    //pmt不等于空
    //子串长度必须要大于0，不然毫无意义
    //字串长度小于目标串长度
    if( (pmt != NULL) && (0 < pl) && (pl < sl))
    {
        for(int i=0,j=0; i<sl; i++)
        {
            while( (j > 0) && (s[i] != p[j]) )//如果匹配不成功，就去找部分匹配表，直到j==0为止跳出循环
            {
                j = pmt[j-1];
            }

            if(s[i] == p[j])//匹配成功
            {
                j++;
            }

            if(j == pl)
            {
                ret = i + 1 - pl;//返回字符串的起始下标
                break;
            }
        }
    }

    return ret;
}

int main()
{
    cout << kmp("ababax","") <<endl;

    return 0;
}

