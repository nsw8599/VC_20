#ifndef _t1466_H_
#define _t1466_H_

///////////////////////////////////////////////////////////////////////////////////////////////////
// 전일동시간대비거래급증(t1466) ( attr,block,headtype=A )
#pragma pack( push, 1 )

#define NAME_t1466     "t1466"

// 기본입력                       
typedef struct _t1466InBlock
{
    char    gubun               [   1];    char    _gubun               ;    // [string,    1] 구분                            StartPos 0, Length 1
    char    type1               [   1];    char    _type1               ;    // [string,    1] 전일거래량                      StartPos 2, Length 1
    char    type2               [   1];    char    _type2               ;    // [string,    1] 거래급등율                      StartPos 4, Length 1
    char    jc_num              [  12];    char    _jc_num              ;    // [long  ,   12] 대상제외                        StartPos 6, Length 12
    char    sprice              [   8];    char    _sprice              ;    // [long  ,    8] 시작가격                        StartPos 19, Length 8
    char    eprice              [   8];    char    _eprice              ;    // [long  ,    8] 종료가격                        StartPos 28, Length 8
    char    volume              [  12];    char    _volume              ;    // [long  ,   12] 거래량                          StartPos 37, Length 12
    char    idx                 [   4];    char    _idx                 ;    // [long  ,    4] IDX                             StartPos 50, Length 4
    char    jc_num2             [  12];    char    _jc_num2             ;    // [long  ,   12] 대상제외2                       StartPos 55, Length 12
    char    exchgubun           [   1];    char    _exchgubun           ;    // [string,    1] 거래소구분코드                  StartPos 68, Length 1
} t1466InBlock, *LPt1466InBlock;
#define NAME_t1466InBlock     "t1466InBlock"

// 출력                           
typedef struct _t1466OutBlock
{
    char    hhmm                [   5];    char    _hhmm                ;    // [string,    5] 현재시분                        StartPos 0, Length 5
    char    idx                 [   4];    char    _idx                 ;    // [long  ,    4] IDX                             StartPos 6, Length 4
} t1466OutBlock, *LPt1466OutBlock;
#define NAME_t1466OutBlock     "t1466OutBlock"

// 출력1                          , occurs
typedef struct _t1466OutBlock1
{
    char    shcode              [   6];    char    _shcode              ;    // [string,    6] 종목코드                        StartPos 0, Length 6
    char    hname               [  20];    char    _hname               ;    // [string,   20] 종목명                          StartPos 7, Length 20
    char    price               [   8];    char    _price               ;    // [long  ,    8] 현재가                          StartPos 28, Length 8
    char    sign                [   1];    char    _sign                ;    // [string,    1] 전일대비구분                    StartPos 37, Length 1
    char    change              [   8];    char    _change              ;    // [long  ,    8] 전일대비                        StartPos 39, Length 8
    char    diff                [   6];    char    _diff                ;    // [double,  6.2] 등락율                          StartPos 48, Length 6
    char    stdvolume           [  12];    char    _stdvolume           ;    // [long  ,   12] 전일거래량                      StartPos 55, Length 12
    char    volume              [  12];    char    _volume              ;    // [long  ,   12] 당일거래량                      StartPos 68, Length 12
    char    voldiff             [   8];    char    _voldiff             ;    // [double,  8.2] 거래급등율                      StartPos 81, Length 8
    char    open                [   8];    char    _open                ;    // [long  ,    8] 시가                            StartPos 90, Length 8
    char    high                [   8];    char    _high                ;    // [long  ,    8] 고가                            StartPos 99, Length 8
    char    low                 [   8];    char    _low                 ;    // [long  ,    8] 저가                            StartPos 108, Length 8
    char    ex_shcode           [  10];    char    _ex_shcode           ;    // [string,   10] 거래소별단축코드                StartPos 117, Length 10
} t1466OutBlock1, *LPt1466OutBlock1;
#define NAME_t1466OutBlock1     "t1466OutBlock1"

#pragma pack( pop )
///////////////////////////////////////////////////////////////////////////////////////////////////

#endif // _t1466_H_
