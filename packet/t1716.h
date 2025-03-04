#ifndef _t1716_H_
#define _t1716_H_

///////////////////////////////////////////////////////////////////////////////////////////////////
// ���α�����񺰵���(t1716) ( attr,block,headtype=A )
#pragma pack( push, 1 )

#define NAME_t1716     "t1716"

// �⺻�Է�                       
typedef struct _t1716InBlock
{
    char    shcode              [   6];    char    _shcode              ;    // [string,    6] �����ڵ�                        StartPos 0, Length 6
    char    gubun               [   1];    char    _gubun               ;    // [string,    1] ����(0:�ϰ����ż�1:�Ⱓ�������� StartPos 7, Length 1
    char    fromdt              [   8];    char    _fromdt              ;    // [string,    8] ��������                        StartPos 9, Length 8
    char    todt                [   8];    char    _todt                ;    // [string,    8] ��������                        StartPos 18, Length 8
    char    prapp               [   3];    char    _prapp               ;    // [long  ,    3] PR����������                    StartPos 27, Length 3
    char    prgubun             [   1];    char    _prgubun             ;    // [string,    1] PR���뱸��(0:�������1:����)    StartPos 31, Length 1
    char    orggubun            [   1];    char    _orggubun            ;    // [string,    1] �������                        StartPos 33, Length 1
    char    frggubun            [   1];    char    _frggubun            ;    // [string,    1] ��������                        StartPos 35, Length 1
    char    exchgubun           [   1];    char    _exchgubun           ;    // [string,    1] �ŷ��ұ����ڵ�                  StartPos 37, Length 1
} t1716InBlock, *LPt1716InBlock;
#define NAME_t1716InBlock     "t1716InBlock"

// ���                           , occurs
typedef struct _t1716OutBlock
{
    char    date                [   8];    char    _date                ;    // [string,    8] ����                            StartPos 0, Length 8
    char    close               [   8];    char    _close               ;    // [long  ,    8] ����                            StartPos 9, Length 8
    char    sign                [   1];    char    _sign                ;    // [string,    1] ���ϴ�񱸺�                    StartPos 18, Length 1
    char    change              [   8];    char    _change              ;    // [long  ,    8] ���ϴ��                        StartPos 20, Length 8
    char    diff                [   6];    char    _diff                ;    // [double,  6.2] �����                          StartPos 29, Length 6
    char    volume              [  12];    char    _volume              ;    // [long  ,   12] �����ŷ���                      StartPos 36, Length 12
    char    krx_0008            [  12];    char    _krx_0008            ;    // [long  ,   12] �ŷ���_����                     StartPos 49, Length 12
    char    krx_0018            [  12];    char    _krx_0018            ;    // [long  ,   12] �ŷ���_���                     StartPos 62, Length 12
    char    krx_0009            [  12];    char    _krx_0009            ;    // [long  ,   12] �ŷ���_�ܱ���                   StartPos 75, Length 12
    char    pgmvol              [  12];    char    _pgmvol              ;    // [long  ,   12] ���α׷�                        StartPos 88, Length 12
    char    fsc_listing         [  12];    char    _fsc_listing         ;    // [long  ,   12] �ݰ���_���κ����ֽļ�           StartPos 101, Length 12
    char    fsc_sjrate          [   6];    char    _fsc_sjrate          ;    // [double,  6.2] �ݰ���_������                   StartPos 114, Length 6
    char    fsc_0009            [  12];    char    _fsc_0009            ;    // [long  ,   12] �ݰ���_�ܱ���                   StartPos 121, Length 12
    char    gm_volume           [  12];    char    _gm_volume           ;    // [long  ,   12] ���ŵ�����                      StartPos 134, Length 12
    char    gm_value            [  12];    char    _gm_value            ;    // [long  ,   12] ���ŵ����                      StartPos 147, Length 12
} t1716OutBlock, *LPt1716OutBlock;
#define NAME_t1716OutBlock     "t1716OutBlock"

#pragma pack( pop )
///////////////////////////////////////////////////////////////////////////////////////////////////

#endif // _t1716_H_
