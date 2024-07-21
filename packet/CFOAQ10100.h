#ifndef _CFOAQ10100_H_
#define _CFOAQ10100_H_

///////////////////////////////////////////////////////////////////////////////////////////////////
// 선물옵션주문가능수량조회 ( SERVICE=CFOAQ10100,HEADTYPE=B,CREATOR=원종혁,CREDATE=2022/02/16 14:27:58 )
#pragma pack( push, 1 )

#define NAME_CFOAQ10100     "CFOAQ10100"

// In(*EMPTY*)                    
typedef struct _CFOAQ10100InBlock1
{
    char    RecCnt              [   5];    // [long  ,    5] 레코드갯수                      StartPos 0, Length 5
    char    AcntNo              [  20];    // [string,   20] 계좌번호                        StartPos 5, Length 20
    char    Pwd                 [   8];    // [string,    8] 비밀번호                        StartPos 25, Length 8
    char    QryTp               [   1];    // [string,    1] 조회구분                        StartPos 33, Length 1
    char    OrdAmt              [  16];    // [long  ,   16] 주문금액                        StartPos 34, Length 16
    char    RatVal              [  19];    // [double, 19.8] 비율값                          StartPos 50, Length 19
    char    FnoIsuNo            [  12];    // [string,   12] 선물옵션종목번호                StartPos 69, Length 12
    char    BnsTpCode           [   1];    // [string,    1] 매매구분                        StartPos 81, Length 1
    char    FnoOrdPrc           [  27];    // [double, 27.8] 선물옵션주문가격                StartPos 82, Length 27
    char    FnoOrdprcPtnCode    [   2];    // [string,    2] 선물옵션호가유형코드            StartPos 109, Length 2
} CFOAQ10100InBlock1, *LPCFOAQ10100InBlock1;
#define NAME_CFOAQ10100InBlock1     "CFOAQ10100InBlock1"

// In(*EMPTY*)                    
typedef struct _CFOAQ10100OutBlock1
{
    char    RecCnt              [   5];    // [long  ,    5] 레코드갯수                      StartPos 0, Length 5
    char    AcntNo              [  20];    // [string,   20] 계좌번호                        StartPos 5, Length 20
    char    Pwd                 [   8];    // [string,    8] 비밀번호                        StartPos 25, Length 8
    char    QryTp               [   1];    // [string,    1] 조회구분                        StartPos 33, Length 1
    char    OrdAmt              [  16];    // [long  ,   16] 주문금액                        StartPos 34, Length 16
    char    RatVal              [  19];    // [double, 19.8] 비율값                          StartPos 50, Length 19
    char    FnoIsuNo            [  12];    // [string,   12] 선물옵션종목번호                StartPos 69, Length 12
    char    BnsTpCode           [   1];    // [string,    1] 매매구분                        StartPos 81, Length 1
    char    FnoOrdPrc           [  27];    // [double, 27.8] 선물옵션주문가격                StartPos 82, Length 27
    char    FnoOrdprcPtnCode    [   2];    // [string,    2] 선물옵션호가유형코드            StartPos 109, Length 2
} CFOAQ10100OutBlock1, *LPCFOAQ10100OutBlock1;
#define NAME_CFOAQ10100OutBlock1     "CFOAQ10100OutBlock1"

// Out(*EMPTY*)                   
typedef struct _CFOAQ10100OutBlock2
{
    char    RecCnt              [   5];    // [long  ,    5] 레코드갯수                      StartPos 0, Length 5
    char    AcntNm              [  40];    // [string,   40] 계좌명                          StartPos 5, Length 40
    char    QryDt               [   8];    // [string,    8] 조회일                          StartPos 45, Length 8
    char    FnoNowPrc           [  27];    // [double, 27.8] 선물옵션현재가                  StartPos 53, Length 27
    char    OrdAbleQty          [  16];    // [long  ,   16] 주문가능수량                    StartPos 80, Length 16
    char    NewOrdAbleQty       [  16];    // [long  ,   16] 신규주문가능수량                StartPos 96, Length 16
    char    LqdtOrdAbleQty      [  16];    // [long  ,   16] 청산주문가능수량                StartPos 112, Length 16
    char    UsePreargMgn        [  16];    // [long  ,   16] 사용예정증거금액                StartPos 128, Length 16
    char    UsePreargMnyMgn     [  16];    // [long  ,   16] 사용예정현금증거금액            StartPos 144, Length 16
    char    OrdAbleAmt          [  16];    // [long  ,   16] 주문가능금액                    StartPos 160, Length 16
    char    MnyOrdAbleAmt       [  16];    // [long  ,   16] 현금주문가능금액                StartPos 176, Length 16
} CFOAQ10100OutBlock2, *LPCFOAQ10100OutBlock2;
#define NAME_CFOAQ10100OutBlock2     "CFOAQ10100OutBlock2"

#pragma pack( pop )
///////////////////////////////////////////////////////////////////////////////////////////////////

#endif // _CFOAQ10100_H_
