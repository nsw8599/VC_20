#ifndef _t1463_H_
#define _t1463_H_

///////////////////////////////////////////////////////////////////////////////////////////////////
// 거래대금상위(t1463) ( attr,block,headtype=A )
#pragma pack( push, 1 )

#define NAME_t1463     "t1463"

// 기본입력                       
typedef struct _t1463InBlock
{
    char    gubun               [   1];    char    _gubun               ;    // [string,    1] 구분                            StartPos 0, Length 1
    char    jnilgubun           [   1];    char    _jnilgubun           ;    // [string,    1] 전일구분                        StartPos 2, Length 1
    char    jc_num              [  12];    char    _jc_num              ;    // [long  ,   12] 대상제외                        StartPos 4, Length 12
    char    sprice              [   8];    char    _sprice              ;    // [long  ,    8] 시작가격                        StartPos 17, Length 8
    char    eprice              [   8];    char    _eprice              ;    // [long  ,    8] 종료가격                        StartPos 26, Length 8
    char    volume              [  12];    char    _volume              ;    // [long  ,   12] 거래량                          StartPos 35, Length 12
    char    idx                 [   4];    char    _idx                 ;    // [long  ,    4] IDX                             StartPos 48, Length 4
    char    jc_num2             [  12];    char    _jc_num2             ;    // [long  ,   12] 대상제외2                       StartPos 53, Length 12
    char    exchgubun           [   1];    char    _exchgubun           ;    // [string,    1] 거래소구분코드                  StartPos 66, Length 1
} t1463InBlock, *LPt1463InBlock;
#define NAME_t1463InBlock     "t1463InBlock"

// 출력                           
typedef struct _t1463OutBlock
{
    char    idx                 [   4];    char    _idx                 ;    // [long  ,    4] IDX                             StartPos 0, Length 4
} t1463OutBlock, *LPt1463OutBlock;
#define NAME_t1463OutBlock     "t1463OutBlock"

// 출력1                          , occurs
typedef struct _t1463OutBlock1
{
    char    hname               [  20];    char    _hname               ;    // [string,   20] 한글명                          StartPos 0, Length 20
    char    price               [   8];    char    _price               ;    // [long  ,    8] 현재가                          StartPos 21, Length 8
    char    sign                [   1];    char    _sign                ;    // [string,    1] 전일대비구분                    StartPos 30, Length 1
    char    change              [   8];    char    _change              ;    // [long  ,    8] 전일대비                        StartPos 32, Length 8
    char    diff                [   6];    char    _diff                ;    // [double,  6.2] 등락율                          StartPos 41, Length 6
    char    volume              [  12];    char    _volume              ;    // [long  ,   12] 누적거래량                      StartPos 48, Length 12
    char    value               [  12];    char    _value               ;    // [long  ,   12] 거래대금                        StartPos 61, Length 12
    char    jnilvalue           [  12];    char    _jnilvalue           ;    // [long  ,   12] 전일거래대금                    StartPos 74, Length 12
    char    bef_diff            [  10];    char    _bef_diff            ;    // [double, 10.2] 전일비                          StartPos 87, Length 10
    char    shcode              [   6];    char    _shcode              ;    // [string,    6] 종목코드                        StartPos 98, Length 6
    char    filler              [   1];    char    _filler              ;    // [string,    1] filler                          StartPos 105, Length 1
    char    jnilvolume          [  12];    char    _jnilvolume          ;    // [long  ,   12] 전일거래량                      StartPos 107, Length 12
    char    ex_shcode           [  10];    char    _ex_shcode           ;    // [string,   10] 거래소별단축코드                StartPos 120, Length 10
} t1463OutBlock1, *LPt1463OutBlock1;
#define NAME_t1463OutBlock1     "t1463OutBlock1"

#pragma pack( pop )
///////////////////////////////////////////////////////////////////////////////////////////////////

#endif // _t1463_H_
