#ifndef _t1441_H_
#define _t1441_H_

///////////////////////////////////////////////////////////////////////////////////////////////////
// 등락율상위(t1441) ( attr,block,headtype=A )
#pragma pack( push, 1 )

#define NAME_t1441     "t1441"

// 기본입력                       
typedef struct _t1441InBlock
{
    char    gubun1              [   1];    char    _gubun1              ;    // [string,    1] 구분                            StartPos 0, Length 1
    char    gubun2              [   1];    char    _gubun2              ;    // [string,    1] 상승하락                        StartPos 2, Length 1
    char    gubun3              [   1];    char    _gubun3              ;    // [string,    1] 당일전일                        StartPos 4, Length 1
    char    jc_num              [  12];    char    _jc_num              ;    // [long  ,   12] 대상제외                        StartPos 6, Length 12
    char    sprice              [   8];    char    _sprice              ;    // [long  ,    8] 시작가격                        StartPos 19, Length 8
    char    eprice              [   8];    char    _eprice              ;    // [long  ,    8] 종료가격                        StartPos 28, Length 8
    char    volume              [  12];    char    _volume              ;    // [long  ,   12] 거래량                          StartPos 37, Length 12
    char    idx                 [   4];    char    _idx                 ;    // [long  ,    4] IDX                             StartPos 50, Length 4
    char    jc_num2             [  12];    char    _jc_num2             ;    // [long  ,   12] 대상제외2                       StartPos 55, Length 12
    char    exchgubun           [   1];    char    _exchgubun           ;    // [string,    1] 거래소구분코드                  StartPos 68, Length 1
} t1441InBlock, *LPt1441InBlock;
#define NAME_t1441InBlock     "t1441InBlock"

// 출력                           
typedef struct _t1441OutBlock
{
    char    idx                 [   4];    char    _idx                 ;    // [long  ,    4] IDX                             StartPos 0, Length 4
} t1441OutBlock, *LPt1441OutBlock;
#define NAME_t1441OutBlock     "t1441OutBlock"

// 출력1                          , occurs
typedef struct _t1441OutBlock1
{
    char    hname               [  20];    char    _hname               ;    // [string,   20] 한글명                          StartPos 0, Length 20
    char    price               [   8];    char    _price               ;    // [long  ,    8] 현재가                          StartPos 21, Length 8
    char    sign                [   1];    char    _sign                ;    // [string,    1] 전일대비구분                    StartPos 30, Length 1
    char    change              [   8];    char    _change              ;    // [long  ,    8] 전일대비                        StartPos 32, Length 8
    char    diff                [   6];    char    _diff                ;    // [double,  6.2] 등락율                          StartPos 41, Length 6
    char    volume              [  12];    char    _volume              ;    // [long  ,   12] 누적거래량                      StartPos 48, Length 12
    char    offerrem1           [  12];    char    _offerrem1           ;    // [long  ,   12] 매도잔량                        StartPos 61, Length 12
    char    offerho1            [  12];    char    _offerho1            ;    // [long  ,   12] 매도호가                        StartPos 74, Length 12
    char    bidho1              [  12];    char    _bidho1              ;    // [long  ,   12] 매수호가                        StartPos 87, Length 12
    char    bidrem1             [  12];    char    _bidrem1             ;    // [long  ,   12] 매수잔량                        StartPos 100, Length 12
    char    updaycnt            [   4];    char    _updaycnt            ;    // [long  ,    4] 연속                            StartPos 113, Length 4
    char    jnildiff            [   6];    char    _jnildiff            ;    // [double,  6.2] 전일등락율                      StartPos 118, Length 6
    char    shcode              [   6];    char    _shcode              ;    // [string,    6] 종목코드                        StartPos 125, Length 6
    char    open                [   8];    char    _open                ;    // [long  ,    8] 시가                            StartPos 132, Length 8
    char    high                [   8];    char    _high                ;    // [long  ,    8] 고가                            StartPos 141, Length 8
    char    low                 [   8];    char    _low                 ;    // [long  ,    8] 저가                            StartPos 150, Length 8
    char    voldiff             [   8];    char    _voldiff             ;    // [double,  8.2] 거래량대비율                    StartPos 159, Length 8
    char    value               [  15];    char    _value               ;    // [long  ,   15] 거래대금                        StartPos 168, Length 15
    char    total               [  12];    char    _total               ;    // [long  ,   12] 시가총액                        StartPos 184, Length 12
    char    ex_shcode           [  10];    char    _ex_shcode           ;    // [string,   10] 거래소별단축코드                StartPos 197, Length 10
} t1441OutBlock1, *LPt1441OutBlock1;
#define NAME_t1441OutBlock1     "t1441OutBlock1"

#pragma pack( pop )
///////////////////////////////////////////////////////////////////////////////////////////////////

#endif // _t1441_H_
