#ifndef _t1638_H_
#define _t1638_H_

///////////////////////////////////////////////////////////////////////////////////////////////////
// �����ܷ�/��������(t1638) ( attr,block,headtype=A )
#pragma pack( push, 1 )

#define NAME_t1638     "t1638"

// �⺻�Է�                       
typedef struct _t1638InBlock
{
    char    gubun1              [   1];    char    _gubun1              ;    // [string,    1] ����                            StartPos 0, Length 1
    char    shcode              [   6];    char    _shcode              ;    // [string,    6] �����ڵ�                        StartPos 2, Length 6
    char    gubun2              [   1];    char    _gubun2              ;    // [string,    1] ����                            StartPos 9, Length 1
    char    exchgubun           [   1];    char    _exchgubun           ;    // [string,    1] �ŷ��ұ����ڵ�                  StartPos 11, Length 1
} t1638InBlock, *LPt1638InBlock;
#define NAME_t1638InBlock     "t1638InBlock"

// ���                           , occurs
typedef struct _t1638OutBlock
{
    char    rank                [   4];    char    _rank                ;    // [long  ,    4] ����                            StartPos 0, Length 4
    char    hname               [  20];    char    _hname               ;    // [string,   20] �ѱ۸�                          StartPos 5, Length 20
    char    price               [   8];    char    _price               ;    // [long  ,    8] ���簡                          StartPos 26, Length 8
    char    sign                [   1];    char    _sign                ;    // [string,    1] ���ϴ�񱸺�                    StartPos 35, Length 1
    char    change              [   8];    char    _change              ;    // [long  ,    8] ���ϴ��                        StartPos 37, Length 8
    char    diff                [   6];    char    _diff                ;    // [float ,  6.2] �����                          StartPos 46, Length 6
    char    sigatotrt           [   6];    char    _sigatotrt           ;    // [float ,  6.2] ���Ѻ���                        StartPos 53, Length 6
    char    obuyvol             [  12];    char    _obuyvol             ;    // [long  ,   12] ���ż��ܷ�                      StartPos 60, Length 12
    char    buyrem              [  12];    char    _buyrem              ;    // [long  ,   12] �ż��ܷ�                        StartPos 73, Length 12
    char    psgvolume           [  12];    char    _psgvolume           ;    // [long  ,   12] �ż����ü���                    StartPos 86, Length 12
    char    sellrem             [  12];    char    _sellrem             ;    // [long  ,   12] �ŵ��ܷ�                        StartPos 99, Length 12
    char    pdgvolume           [  12];    char    _pdgvolume           ;    // [long  ,   12] �ŵ����ü���                    StartPos 112, Length 12
    char    sigatot             [  20];    char    _sigatot             ;    // [long  ,   20] �ð��Ѿ�                        StartPos 125, Length 20
    char    shcode              [   6];    char    _shcode              ;    // [string,    6] �����ڵ�                        StartPos 146, Length 6
} t1638OutBlock, *LPt1638OutBlock;
#define NAME_t1638OutBlock     "t1638OutBlock"

#pragma pack( pop )
///////////////////////////////////////////////////////////////////////////////////////////////////

#endif // _t1638_H_
