# Repo-codes #
## My code repository ##

### Including ###
  * Solved OI or acm/icpc oj problems, including:
    * WOJ http://acm.whu.edu.cn
    * PKU http://acm.pku.edu.cn
    * HUSTOJ http://acm.hust.edu.cn/judge/
    * FeliOJ http://acm.whu.edu.cn/felioj/
    * ZJU http://acm.zju.edu.cn
    * USACO http://train.usaco.org/usacogate
    * SGU http://acm.sgu.ru
    * TJU

  * Crypto related programs
    * AES using libcrypto++
    * DES using openssl crypto library
    * SHA1 using openssl crypto library
    * base64 C implementation
    * TinyPRP, Permutation Generator, see paper Enciphering with Arbitrary Small Finite Domains
    * Feistel-DES Permutation Generator, see paper Ciphers with Arbitrary Finite Domains
    * Feistel-TinyPRP Permutation Generator, the combination of above two, and use TinyPRP substitutes the DES, see directory feistel\_pg

  * XML
    * Perl and C version XML access examples, along with a regex example in C

  * Database
    * Perl and C version mysql access examples

  * Timers
    * timer0.c --- Direct read the hardware timer, most accurate which can reach nanosecond level, but it only counts the system. This version may behave abnormally in X86\_64 environment, I have no idea about it currently
    * timer1.c --- Can get both cpu as well as system time. The accuracy is low. It seems to be 10ms, which I really forget
    * timer2.c --- Can get cpu time. The accuracy seems to be the same as the method in timer1.c
    * timer3.c --- Can get both cpu and system time. The accuracy is about millisecond
    * timer4.c --- Can get both cpu and system time. The accuracy is about nanosencond

  * GCC plugins (See README file in the directory for more details)
    * test --- The codes here are actually refered and modified from http://www.kdedevelopers.org/node/3945. The function is given a pass name, gcc will dump the cooresponding infomation while compiling
    * get\_ast --- Extract AST in gcc front-end, which means it has not change to gimple yet.
    * get\_ast\_from\_gimple --- Somthing similar to the get\_ast, but this time we extract from the gimple, and in the meanwhile we have basic blocks ready now.
    * gimple\_modify\_code --- Somthing similar to the get\_ast, but this time we extract from the gimple, and in the meanwhile we have basic blocks ready now.