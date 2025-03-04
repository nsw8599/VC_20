#ifndef _VI__H_
#define _VI__H_

///////////////////////////////////////////////////////////////////////////////////////////////////
// VI발동해제(VI_) ( attr,key=6,group=1 )
#pragma pack( push, 1 )

#define NAME_VI_     "VI_"

// 입력                           
typedef struct _VI__InBlock
{
    char    shcode              [   6];    char    _shcode              ;    // [string,    6] 단축코드(KEY)                   StartPos 0, Length 6
} VI__InBlock, *LPVI__InBlock;
#define NAME_VI__InBlock     "InBlock"

// 출력                           
typedef struct _VI__OutBlock
{
    char    vi_gubun            [   1];    char    _vi_gubun            ;    // [string,    1] 구분(0:해제 1:정적발동 2:동적발 StartPos 0, Length 1
    char    svi_recprice        [   8];    char    _svi_recprice        ;    // [long  ,    8] 정적VI발동기준가격              StartPos 2, Length 8
    char    dvi_recprice        [   8];    char    _dvi_recprice        ;    // [long  ,    8] 동적VI발동기준가격              StartPos 11, Length 8
    char    vi_trgprice         [   8];    char    _vi_trgprice         ;    // [long  ,    8] VI발동가격                      StartPos 20, Length 8
    char    shcode              [   6];    char    _shcode              ;    // [string,    6] 단축코드(KEY)                   StartPos 29, Length 6
    char    ref_shcode          [   6];    char    _ref_shcode          ;    // [string,    6] 참조코드(미사용)                StartPos 36, Length 6
    char    time                [   6];    char    _time                ;    // [string,    6] 시간                            StartPos 43, Length 6
    char    exchname            [   3];    char    _exchname            ;    // [string,    3] 거래소명                        StartPos 50, Length 3
} VI__OutBlock, *LPVI__OutBlock;
#define NAME_VI__OutBlock     "OutBlock"

#pragma pack( pop )
///////////////////////////////////////////////////////////////////////////////////////////////////

#endif // _VI__H_
