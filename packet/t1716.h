#ifndef _t1716_H_
#define _t1716_H_

///////////////////////////////////////////////////////////////////////////////////////////////////
// 외인기관종목별동향(t1716) ( attr,block,headtype=A )
#pragma pack( push, 1 )

#define NAME_t1716     "t1716"

// 기본입력                       
typedef struct _t1716InBlock
{
    char    shcode              [   6];    char    _shcode              ;    // [string,    6] 종목코드                        StartPos 0, Length 6
    char    gubun               [   1];    char    _gubun               ;    // [string,    1] 구분(0:일간순매수1:기간누적순매 StartPos 7, Length 1
    char    fromdt              [   8];    char    _fromdt              ;    // [string,    8] 시작일자                        StartPos 9, Length 8
    char    todt                [   8];    char    _todt                ;    // [string,    8] 종료일자                        StartPos 18, Length 8
    char    prapp               [   3];    char    _prapp               ;    // [long  ,    3] PR감산적용율                    StartPos 27, Length 3
    char    prgubun             [   1];    char    _prgubun             ;    // [string,    1] PR적용구분(0:적용안함1:적용)    StartPos 31, Length 1
    char    orggubun            [   1];    char    _orggubun            ;    // [string,    1] 기관적용                        StartPos 33, Length 1
    char    frggubun            [   1];    char    _frggubun            ;    // [string,    1] 외인적용                        StartPos 35, Length 1
    char    exchgubun           [   1];    char    _exchgubun           ;    // [string,    1] 거래소구분코드                  StartPos 37, Length 1
} t1716InBlock, *LPt1716InBlock;
#define NAME_t1716InBlock     "t1716InBlock"

// 출력                           , occurs
typedef struct _t1716OutBlock
{
    char    date                [   8];    char    _date                ;    // [string,    8] 일자                            StartPos 0, Length 8
    char    close               [   8];    char    _close               ;    // [long  ,    8] 종가                            StartPos 9, Length 8
    char    sign                [   1];    char    _sign                ;    // [string,    1] 전일대비구분                    StartPos 18, Length 1
    char    change              [   8];    char    _change              ;    // [long  ,    8] 전일대비                        StartPos 20, Length 8
    char    diff                [   6];    char    _diff                ;    // [double,  6.2] 등락율                          StartPos 29, Length 6
    char    volume              [  12];    char    _volume              ;    // [long  ,   12] 누적거래량                      StartPos 36, Length 12
    char    krx_0008            [  12];    char    _krx_0008            ;    // [long  ,   12] 거래소_개인                     StartPos 49, Length 12
    char    krx_0018            [  12];    char    _krx_0018            ;    // [long  ,   12] 거래소_기관                     StartPos 62, Length 12
    char    krx_0009            [  12];    char    _krx_0009            ;    // [long  ,   12] 거래소_외국인                   StartPos 75, Length 12
    char    pgmvol              [  12];    char    _pgmvol              ;    // [long  ,   12] 프로그램                        StartPos 88, Length 12
    char    fsc_listing         [  12];    char    _fsc_listing         ;    // [long  ,   12] 금감원_외인보유주식수           StartPos 101, Length 12
    char    fsc_sjrate          [   6];    char    _fsc_sjrate          ;    // [double,  6.2] 금감원_소진율                   StartPos 114, Length 6
    char    fsc_0009            [  12];    char    _fsc_0009            ;    // [long  ,   12] 금감원_외국인                   StartPos 121, Length 12
    char    gm_volume           [  12];    char    _gm_volume           ;    // [long  ,   12] 공매도수량                      StartPos 134, Length 12
    char    gm_value            [  12];    char    _gm_value            ;    // [long  ,   12] 공매도대금                      StartPos 147, Length 12
} t1716OutBlock, *LPt1716OutBlock;
#define NAME_t1716OutBlock     "t1716OutBlock"

#pragma pack( pop )
///////////////////////////////////////////////////////////////////////////////////////////////////

#endif // _t1716_H_
