#ifndef _DVI_H_
#define _DVI_H_

///////////////////////////////////////////////////////////////////////////////////////////////////
// �ð��ܴ��ϰ�VI�ߵ�����(DVI) ( attr,key=6,group=1 )
#pragma pack( push, 1 )

#define NAME_DVI     "DVI"

// �Է�                           
typedef struct _DVI_InBlock
{
    char    shcode              [   6];    char    _shcode              ;    // [string,    6] �����ڵ�(KEY)                   StartPos 0, Length 6
} DVI_InBlock, *LPDVI_InBlock;
#define NAME_DVI_InBlock     "InBlock"

// ���                           
typedef struct _DVI_OutBlock
{
    char    vi_gubun            [   1];    char    _vi_gubun            ;    // [string,    1] ����(0:���� 1:�����ߵ� 2:������ StartPos 0, Length 1
    char    svi_recprice        [   8];    char    _svi_recprice        ;    // [long  ,    8] ����VI�ߵ����ذ���              StartPos 2, Length 8
    char    dvi_recprice        [   8];    char    _dvi_recprice        ;    // [long  ,    8] ����VI�ߵ����ذ���              StartPos 11, Length 8
    char    vi_trgprice         [   8];    char    _vi_trgprice         ;    // [long  ,    8] VI�ߵ�����                      StartPos 20, Length 8
    char    shcode              [   6];    char    _shcode              ;    // [string,    6] �����ڵ�(KEY)                   StartPos 29, Length 6
    char    ref_shcode          [   6];    char    _ref_shcode          ;    // [string,    6] �����ڵ�(�̻��)                StartPos 36, Length 6
    char    time                [   6];    char    _time                ;    // [string,    6] �ð�                            StartPos 43, Length 6
    char    exchname            [   3];    char    _exchname            ;    // [string,    3] �ŷ��Ҹ�                        StartPos 50, Length 3
} DVI_OutBlock, *LPDVI_OutBlock;
#define NAME_DVI_OutBlock     "OutBlock"

#pragma pack( pop )
///////////////////////////////////////////////////////////////////////////////////////////////////

#endif // _DVI_H_
