#ifndef _t1638_H_
#define _t1638_H_

///////////////////////////////////////////////////////////////////////////////////////////////////
// 종목별잔량/사전공시(t1638) ( attr,block,headtype=A )
#pragma pack( push, 1 )

#define NAME_t1638     "t1638"

// 기본입력                       
typedef struct _t1638InBlock
{
    char    gubun1              [   1];    char    _gubun1              ;    // [string,    1] 구분                            StartPos 0, Length 1
    char    shcode              [   6];    char    _shcode              ;    // [string,    6] 종목코드                        StartPos 2, Length 6
    char    gubun2              [   1];    char    _gubun2              ;    // [string,    1] 정렬                            StartPos 9, Length 1
    char    exchgubun           [   1];    char    _exchgubun           ;    // [string,    1] 거래소구분코드                  StartPos 11, Length 1
} t1638InBlock, *LPt1638InBlock;
#define NAME_t1638InBlock     "t1638InBlock"

// 출력                           , occurs
typedef struct _t1638OutBlock
{
    char    rank                [   4];    char    _rank                ;    // [long  ,    4] 순위                            StartPos 0, Length 4
    char    hname               [  20];    char    _hname               ;    // [string,   20] 한글명                          StartPos 5, Length 20
    char    price               [   8];    char    _price               ;    // [long  ,    8] 현재가                          StartPos 26, Length 8
    char    sign                [   1];    char    _sign                ;    // [string,    1] 전일대비구분                    StartPos 35, Length 1
    char    change              [   8];    char    _change              ;    // [long  ,    8] 전일대비                        StartPos 37, Length 8
    char    diff                [   6];    char    _diff                ;    // [float ,  6.2] 등락율                          StartPos 46, Length 6
    char    sigatotrt           [   6];    char    _sigatotrt           ;    // [float ,  6.2] 시총비중                        StartPos 53, Length 6
    char    obuyvol             [  12];    char    _obuyvol             ;    // [long  ,   12] 순매수잔량                      StartPos 60, Length 12
    char    buyrem              [  12];    char    _buyrem              ;    // [long  ,   12] 매수잔량                        StartPos 73, Length 12
    char    psgvolume           [  12];    char    _psgvolume           ;    // [long  ,   12] 매수공시수량                    StartPos 86, Length 12
    char    sellrem             [  12];    char    _sellrem             ;    // [long  ,   12] 매도잔량                        StartPos 99, Length 12
    char    pdgvolume           [  12];    char    _pdgvolume           ;    // [long  ,   12] 매도공시수량                    StartPos 112, Length 12
    char    sigatot             [  20];    char    _sigatot             ;    // [long  ,   20] 시가총액                        StartPos 125, Length 20
    char    shcode              [   6];    char    _shcode              ;    // [string,    6] 종목코드                        StartPos 146, Length 6
} t1638OutBlock, *LPt1638OutBlock;
#define NAME_t1638OutBlock     "t1638OutBlock"

#pragma pack( pop )
///////////////////////////////////////////////////////////////////////////////////////////////////

#endif // _t1638_H_
