#include<vector>
#include<utility>
#include<string>
using namespace std;
#define ull unsigned long long

namespace ftr{
    ull unllgcd(ull a, ull b) {//求最大公约数，默认a>=b
        if (b == 0)return a;
        return unllgcd(b,a % b);
    }
    pair<ull, ull> jiance(vector<short> &n) {
        //检测循环部分，返回循环的开始和结束（左闭右闭）
        ull h1[10] = {}/*初始化全为0*/;//使用哈希表记录数字出现的次数
        ull h2[10] = {};//同理，第二轮遍历时使用

        for (short& i : n)h1[i]++;//第一轮遍历记录每个数字的总出现次数（使用迭代器）
        bool flag = true;//用于记录是否要检测循环部分
        for (int i = 0; i < 10; i++) {//检测出现次数是否全为偶数，是则检查是否为循环部分
            if (h1[i] & 1/*位运算优化 等价于  h1[i] % 2 == 1  (十次其实可有可无)*/) {
                flag = false;//检测到奇数修改为不检测循环部分
                break;
            }
        }
        if (flag) {
            //检测是否循环
            //使用双指针
            //这段改的比较多不写小注释了
            //原理为不断将循环范围减半直到不循环为止如果第一轮不循环侧进入第二轮遍历
            ull i1 = 0, i2 = n.size();
            ull ti1, ti2;//缩减后的两个下标
            bool ok = true;//用于记录是否缩减成功
            while (!(i2 & 1) and ok) {
                ti1 = 0;
                ti2 = i2 >> 1;
                while (ti2 < i2) {
                    if (n[ti1] != n[ti2]) {
                        ok = false;
                        break;
                    }
                    ti1++;
                    ti2++;
                }if (ok) {//如果循环更新值
                    i2 >>= 1;
                }
                else if(i2 == n.size()){//
                    break;
                }
                else {
                    return { 0,i2 - 1 };
                }
            }if (ok) {//如果保持循环返回
                return { 0,i2 - 1 };
            }
        }

        for (ull i = 0; i < n.size();i++) {//第二轮遍历
            h2[n[i]]++;//更新第二轮的情况

            //begin
            flag = true;
            for (int j = 0; j < 10; j++) {
                if ((h1[j] - h2[j]) & 1) {//这里用h1[i] - h2[i]表示后面区间的数字统计
                    flag = false;
                    break;
                }
            }
            if (flag) {
                ull i1 = i + 1, i2 = n.size();
                ull ti1, ti2;
                bool ok = true;
                while (!((i2 - i1) & 1) and ok) {
                    ti1 = i1;
                    ti2 = i1 + ((i2 - i1) >> 1);
                    while (ti2 < i2) {
                        if (n[ti1] != n[ti2]) {
                            ok = false;
                            break;
                        }
                        ti1++;
                        ti2++;
                    }if (ok) {
                        i2 = i1 + ((i2 - i1) >> 1);
                    }else if (i2 == n.size()) {
                        break;
                    }else {
                        return { i1,i2 - 1 };
                    }
                }if (ok) {//如果保持循环返回
                    return { i1,i2 - 1 };
                }
            }
            //end
        }
        return { 0,0 };

    }
    pair<ull, ull> float_to_rational(const string num) {
        //返回值第一个为分子第二个为分母
        ull up = 0, down = 1;//up分子，down分母
        ull i = 0;//当前下标
        while (num[i] != '.'/*直到指向小数点为止*/) {//处理整数部分
            up *= 10;//将分子按十进制左移
            up += num[i] - '0';//添加数位
            i++;//指向下一位
        }
        i++;//指向小数点下一位

        //处理小数部分
        vector<short> n;//使用vector容器暂时存储小数位
        while (i < num.size()/*大于长度退出*/ and num[i] != '.'/*检测到小数点退出*/) {
            n.emplace_back(num[i] - '0');//添加数位到容器
            i++;//指向下一位
        }
        if (i == num.size()) {//检查是否为循环小数
            //处理不循环小数
            //直接添加到末尾
            for (short& i : n) {//使用迭代器遍历
                up *= 10;//将分子按十进制左移
                up += i;//添加数位
                down *= 10;//将分母按十进制左移
            }
        }else {
            //处理循环小数
            //先检测循环部分，再将不循环部分直接添加，再加（循环部分/999...9（循环部分长度个9）/pow（10，len（不循环部分）））
            pair<ull,ull> xun = jiance(n);

            //用变量临时记录循环部分
            ull xup = 0, xdown = 0;
            for (int i = xun.first; i <= xun.second; i++) {
                xup *= 10;
                xup += n[i];
                xdown *= 10;
                xdown += 9;
            }

            //将不循环部分添加
            for (int i = 0;i < xun.first; i++) {
                up *= 10;//将分子按十进制左移
                up += n[i];//添加数位
                down *= 10;//将分母按十进制左移
            }

            //通分
            up *= xdown;
            down *= xdown;
            for (int i = 0; i < xun.first; i++) {
                xdown *= 10;
            }

            //相加
            up += xup;
        }
        //约分化简，使用gcd
        ull g = unllgcd(up, down);
        up /= g;
        down /= g;

        //返回
        return { up,down };
    }
}
int main() {
    auto a = ftr::float_to_rational("1.6385454...");//循环小数示例1（只要小数部分最后为.就是循环小数）
    printf("%lld/%lld\n", a.first, a.second);
    a = ftr::float_to_rational("7.5454...");//循环小数示例2
    printf("%lld/%lld\n", a.first, a.second);
    a = ftr::float_to_rational("11.555.");//循环小数示例3
    printf("%lld/%lld\n", a.first, a.second);
    a = ftr::float_to_rational("5.638");//有限小数示例
    printf("%lld/%lld", a.first, a.second);
}
