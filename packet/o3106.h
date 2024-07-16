#ifndef _o3106_H_
#define _o3106_H_

///////////////////////////////////////////////////////////////////////////////////////////////////
// 해외선물 호가 ( ATTR,BLOCK,SVR=OVS,HEADTYPE=A )
#pragma pack( push, 1 )

#define NAME_o3106     "o3106"

// 기본입력                       
typedef struct _o3106InBlock
{
    char    symbol              [   8];    char    _symbol              ;    // [string,    8] 단축코드                        StartPos 0, Length 8
} o3106InBlock, *LPo3106InBlock;
#define NAME_o3106InBlock     "o3106InBlock"

// 출력                           
typedef struct _o3106OutBlock
{
    char    symbol              [   8];    char    _symbol              ;    // [string,    8] 종목코드                        StartPos 0, Length 8
    char    symbolname          [  50];    char    _symbolname          ;    // [string,   50] 종목명                          StartPos 9, Length 50
    char    price               [  15];    char    _price               ;    // [double, 15.9] 현재가                          StartPos 60, Length 15
    char    sign                [   1];    char    _sign                ;    // [string,    1] 전일대비구분                    StartPos 76, Length 1
    char    change              [  15];    char    _change              ;    // [double, 15.9] 전일대비                        StartPos 78, Length 15
    char    diff                [   6];    char    _diff                ;    // [float ,  6.2] 등락율                          StartPos 94, Length 6
    char    volume              [  10];    char    _volume              ;    // [long  ,   10] 누적거래량                      StartPos 101, Length 10
    char    jnilclose           [  15];    char    _jnilclose           ;    // [double, 15.9] 전일종가                        StartPos 112, Length 15
    char    open                [  15];    char    _open                ;    // [double, 15.9] 시가                            StartPos 128, Length 15
    char    high                [  15];    char    _high                ;    // [double, 15.9] 고가                            StartPos 144, Length 15
    char    low                 [  15];    char    _low                 ;    // [double, 15.9] 저가                            StartPos 160, Length 15
    char    hotime              [   6];    char    _hotime              ;    // [string,    6] 호가수신시간                    StartPos 176, Length 6
    char    offerho1            [  15];    char    _offerho1            ;    // [double, 15.9] 매도호가1                       StartPos 183, Length 15
    char    bidho1              [  15];    char    _bidho1              ;    // [double, 15.9] 매수호가1                       StartPos 199, Length 15
    char    offercnt1           [  10];    char    _offercnt1           ;    // [long  ,   10] 매도호가건수1                   StartPos 215, Length 10
    char    bidcnt1             [  10];    char    _bidcnt1             ;    // [long  ,   10] 매수호가건수1                   StartPos 226, Length 10
    char    offerrem1           [  10];    char    _offerrem1           ;    // [long  ,   10] 매도호가수량1                   StartPos 237, Length 10
    char    bidrem1             [  10];    char    _bidrem1             ;    // [long  ,   10] 매수호가수량1                   StartPos 248, Length 10
    char    offerho2            [  15];    char    _offerho2            ;    // [double, 15.9] 매도호가2                       StartPos 259, Length 15
    char    bidho2              [  15];    char    _bidho2              ;    // [double, 15.9] 매수호가2                       StartPos 275, Length 15
    char    offercnt2           [  10];    char    _offercnt2           ;    // [long  ,   10] 매도호가건수2                   StartPos 291, Length 10
    char    bidcnt2             [  10];    char    _bidcnt2             ;    // [long  ,   10] 매수호가건수2                   StartPos 302, Length 10
    char    offerrem2           [  10];    char    _offerrem2           ;    // [long  ,   10] 매도호가수량2                   StartPos 313, Length 10
    char    bidrem2             [  10];    char    _bidrem2             ;    // [long  ,   10] 매수호가수량2                   StartPos 324, Length 10
    char    offerho3            [  15];    char    _offerho3            ;    // [double, 15.9] 매도호가3                       StartPos 335, Length 15
    char    bidho3              [  15];    char    _bidho3              ;    // [double, 15.9] 매수호가3                       StartPos 351, Length 15
    char    offercnt3           [  10];    char    _offercnt3           ;    // [long  ,   10] 매도호가건수3                   StartPos 367, Length 10
    char    bidcnt3             [  10];    char    _bidcnt3             ;    // [long  ,   10] 매수호가건수3                   StartPos 378, Length 10
    char    offerrem3           [  10];    char    _offerrem3           ;    // [long  ,   10] 매도호가수량3                   StartPos 389, Length 10
    char    bidrem3             [  10];    char    _bidrem3             ;    // [long  ,   10] 매수호가수량3                   StartPos 400, Length 10
    char    offerho4            [  15];    char    _offerho4            ;    // [double, 15.9] 매도호가4                       StartPos 411, Length 15
    char    bidho4              [  15];    char    _bidho4              ;    // [double, 15.9] 매수호가4                       StartPos 427, Length 15
    char    offercnt4           [  10];    char    _offercnt4           ;    // [long  ,   10] 매도호가건수4                   StartPos 443, Length 10
    char    bidcnt4             [  10];    char    _bidcnt4             ;    // [long  ,   10] 매수호가건수4                   StartPos 454, Length 10
    char    offerrem4           [  10];    char    _offerrem4           ;    // [long  ,   10] 매도호가수량4                   StartPos 465, Length 10
    char    bidrem4             [  10];    char    _bidrem4             ;    // [long  ,   10] 매수호가수량4                   StartPos 476, Length 10
    char    offerho5            [  15];    char    _offerho5            ;    // [double, 15.9] 매도호가5                       StartPos 487, Length 15
    char    bidho5              [  15];    char    _bidho5              ;    // [double, 15.9] 매수호가5                       StartPos 503, Length 15
    char    offercnt5           [  10];    char    _offercnt5           ;    // [long  ,   10] 매도호가건수5                   StartPos 519, Length 10
    char    bidcnt5             [  10];    char    _bidcnt5             ;    // [long  ,   10] 매수호가건수5                   StartPos 530, Length 10
    char    offerrem5           [  10];    char    _offerrem5           ;    // [long  ,   10] 매도호가수량5                   StartPos 541, Length 10
    char    bidrem5             [  10];    char    _bidrem5             ;    // [long  ,   10] 매수호가수량5                   StartPos 552, Length 10
    char    offercnt            [  10];    char    _offercnt            ;    // [long  ,   10] 매도호가건수합                  StartPos 563, Length 10
    char    bidcnt              [  10];    char    _bidcnt              ;    // [long  ,   10] 매수호가건수합                  StartPos 574, Length 10
    char    offer               [  10];    char    _offer               ;    // [long  ,   10] 매도호가수량합                  StartPos 585, Length 10
    char    bid                 [  10];    char    _bid                 ;    // [long  ,   10] 매수호가수량합                  StartPos 596, Length 10
} o3106OutBlock, *LPo3106OutBlock;
#define NAME_o3106OutBlock     "o3106OutBlock"

#pragma pack( pop )
///////////////////////////////////////////////////////////////////////////////////////////////////

#endif // _o3106_H_
