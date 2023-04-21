# memtester_mcu
- 源自https://pyropus.ca./software/memtester/
- 公众号文章-https://mp.weixin.qq.com/s/boRYlDWEzgmDLoRaDM9Vvg 欢迎关注

- 本项目移植自https://github.com/jnavila/memtester
  使得其移植性更好,更适合于MCU使用

- 重新命名了文件名,防止添加到项目中文件名重复

- 头文件添加了防止重复包含宏处理,支持c++调用

- 将putchar和fprintf统一为memtester_printf,方便移植

# 依赖

- `<string.h>`:`memset`

- `<stdlib.h>`:`rand`

- `<limits.h>`:`ULONG_MAX`

- `memtester_types.h`中需要
  
  定义几个数据类型,`ull`未使用,`ul`为无符号基本数据类型。
  
  ```
  typedef unsigned long ul;
  typedef unsigned long long ull;
  typedef unsigned long volatile ulv;
  typedef unsigned char volatile u8v;
  typedef unsigned short volatile u16v;
  ```
  
  需实现memtester_printf

- 
