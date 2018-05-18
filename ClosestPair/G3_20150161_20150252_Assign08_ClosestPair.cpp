// GROUP:   3
// ID:      20150161
// ID:      20150252
// Assign:  08
// Assign:  ClosetsPair
// UVA:     10245
// Name1:   Abdallah Mostafa Mokhtar
// Name2:   Mostaga El-Sayed
// UVA Username: abdallah_mostafa

#include <cstdio>
#include <cstdlib>
#include<iomanip>
#include <cstring>
#include <iostream>
#include <cmath>     // please use the built-in sqrt() function
using namespace std;

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid = n/2;
    int i = 0, j = mid, k;
    Type *t = new Type[n];
    for(k = 0; k < n; k++) //o(n)
    {
        if(j==n || (i < mid && IsBefore(a[i], a[j])))
        {
            t[k] = a[i++];
        }
        else
        {
            t[k] = a[j++];
        }
    }
    for(int i = 0; i < n; i++)
    {
        a[i] = t[i];
    }
    delete [] t;
}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid = n/2;
    if(n<=1)
    {
        return;
    }
    MergeSort<Type>(a, mid, IsBefore);
    MergeSort<Type>(a+mid, n-mid, IsBefore);
    Merge<Type>(a, n, IsBefore);
}

struct Point
{
    double x,y;
};

bool IsBeforeX(Point& a, Point& b)
{
    return a.x < b.x;
}
bool IsBeforeY(Point& a, Point& b)
{
    return a.y < b.y;
}

double dist(Point& a, Point& b)
{
    double x1, x2, y1, y2, x1_x2, y1_y2, x_x, y_y;
    x1 = a.x;
    x2 = b.x;
    y1 = a.y;
    y2 = b.y;
    x1_x2 = x2 - x1;
    y1_y2 = y2 - y1;
    x_x = x1_x2 * x1_x2;
    y_y = y1_y2 * y1_y2;
    return sqrt(x_x + y_y);
}

// Sort the points p according to x before calling this function
double ClosestPair(Point* p, int n)
{
    double smallest = 1111111111111;
    int mid = n/2;
    if(n <=3 )
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = i+1 ; j < n; j++)
            {
                if(dist(p[i],p[j]) < smallest)
                {
                    smallest = dist(p[i],p[j]);
                }
            }
        }
        return smallest;
    }
    double x = ClosestPair(p, mid);
    double y = ClosestPair(p+mid, n - mid);
    Point *strip;
    smallest = min(x,y);
    strip = new Point[n];
    int j = 0;
    for(int i = 0,j = 0; i < n; i++)
    {
        if((abs(p[i].x - p[mid].x) < smallest))
            strip[j++] = p[i];
    }
    //cout<<j << "<<<<<<<" <<endl;
    MergeSort(strip,j,IsBeforeY);
    for(int i = 0; i < j; i++)
    {
        for(int k = i+1; k < j && strip[k].y - strip[i].y < smallest; k++)
        {
            if(dist(strip[i],strip[k]) < smallest)
                smallest = dist(strip[i],strip[k]);
        }
    }
    delete [] strip;
    return smallest;
}

int main()
{
    freopen("out.txt","w",stdout);
    int test;
    cin>>test;
    Point *point;
    while(test != 0)
    {
        point = new Point[test];
        for(int i = 0; i < test; i++)
            cin>>point[i].x>>point[i].y;
        //cout<<"hhhhhh" <<endl;
        MergeSort(point,test,IsBeforeX);
        double minum = ClosestPair(point,test);
        if(minum > 10000)
            cout<<"INFINITY"<<endl;
        else
            cout<<fixed<<setprecision(4)<<minum<<endl;
        delete []point;
        cin>>test;
//        for(int i = 0; i < test; i++)
//        {
//            if(point[i].x > minum )
//        }
    }
    return 0;
}
/*

646
37291 24202
30415 18484
8264 35482
31971 6687
7441 34427
9500 36937
26577 35119
3626 8248
22256 25690
7619 31309
9267 21956
14764 753
13259 15144
14312 37985
8703 24128
36453 547
26244 6641
1413 33662
33527 1719
16061 12459
39107 12950
20545 37790
34673 6510
35259 590
13168 22308
3174 24414
17424 10156
13859 1760
19363 38423
39962 1196
9658 27125
9322 2067
16657 19970
37601 27489
14034 16996
31982 17654
12295 7211
39099 25608
6602 26225
38363 24558
12183 2480
9133 34654
111 17870
2294 28592
5736 7317
19841 9347
1847 4865
20476 37512
17206 17851
21558 32242
35601 30600
14694 16958
31450 36091
31191 16084
31406 22428
19432 24703
5682 22000
13266 12554
36023 20085
31256 27426
27663 10341
17614 8239
14159 1129
38369 39113
34541 6427
37477 974
10838 22601
36623 16678
3557 3637
35481 33012
27202 28125
837 23462
17450 31024
25461 32695
20813 24742
18788 8827
39963 37332
36619 19931
38039 7229
32445 24501
8912 7639
5959 18032
38366 16205
13589 14434
5010 125
22176 37012
38072 14238
4144 29350
10462 15327
3715 21386
7767 39745
3701 31201
28314 25194
31280 33930
25238 23809
26161 35334
23329 27968
18131 1394
17392 18481
6615 36744
20 9979
1331 38792
38834 4219
33822 3045
2307 25157
9084 18434
30370 37569
3864 11885
18061 25858
1321 28851
31650 28860
27865 31291
31224 21589
16022 38392
21409 17667
34810 33171
38705 19568
21607 18359
1710 3558
23999 7304
23392 10768
29338 1813
422 32491
3173 35718
27723 10102
5337 21873
23155 34493
16696 22938
36267 35101
23951 33265
10403 28519
19180 31648
25243 4683
6030 26574
38920 12918
23526 21760
21488 28923
19344 14485
12033 7667
4333 30931
36579 16179
7040 26265
7590 30606
2293 17341
33119 30233
2693 37300
13547 12722
15098 29628
37966 33353
9971 3680
7660 25910
29589 26332
31288 23232
2943 39428
15917 30038
13986 29681
10741 10107
4348 27212
13411 14728
23964 12912
14927 28966
25324 701
18303 40
23744 14913
12912 31110
17298 24875
24443 16597
36949 37228
22692 10324
12055 35730
30972 632
12884 33123
28684 37470
34321 4458
11771 5278
8631 11598
7729 13406
24940 13241
583 14616
14037 36568
18986 14183
15066 25963
31367 23673
6817 5749
28100 10644
26927 35410
15102 39192
10921 39479
9827 12185
24197 29993
31737 8011
33110 21586
35354 20396
29414 28417
27678 24520
4945 1561
32012 1401
23850 4361
23562 19198
23601 20834
38078 18049
7976 282
16640 36989
9570 19713
10821 3243
4822 18481
29436 39181
22464 12271
24452 31987
506 30245
21251 26344
38773 39428
8083 28175
35624 21590
7240 32854
30924 36626
15477 19949
26763 25070
37343 14318
8047 9469
418 21868
14308 4548
14575 29705
19581 21479
19010 9467
14950 2739
34019 21555
39048 12569
3009 4327
37105 36538
25274 8863
33480 37321
17036 8374
8058 26747
31488 16498
8148 24903
37714 6877
27599 36918
30557 26304
23103 24745
19780 17052
4708 9097
39785 14495
21869 23464
31485 9812
6141 2769
27437 9800
23694 15065
19089 33203
35531 23533
24151 31059
6476 13403
37204 22467
2970 17913
19013 38828
9043 19855
25289 17406
30319 12692
23757 9946
37471 10880
23712 30939
30178 39382
28630 12085
16237 14648
37817 30912
6483 24876
28020 13509
12211 18264
28164 6718
2990 6516
29372 25082
28855 24093
37187 28986
306 22306
16825 1171
27702 12184
14845 27949
29495 2466
37567 8728
37051 643
19936 27722
10351 428
8626 11307
25427 33138
32763 10520
715 30850
11128 5768
9772 18489
9732 33236
32648 3623
24494 12787
29372 22830
31690 12046
16816 29259
24024 14053
37435 4161
35853 31970
13459 19205
25819 15156
21365 32472
4798 19954
18637 30999
32954 16221
5029 24311
26746 19788
26565 25248
23853 10335
14797 24498
11385 23765
26814 5266
19162 194
8144 27065
3088 1550
7768 4449
24356 27575
31392 5877
9975 16811
34456 8279
607 38057
29331 6751
31505 6104
24027 1637
35584 39767
37998 16561
21761 4994
23710 25991
33591 18256
27365 30010
27844 5731
19741 13007
25645 2779
25002 34260
16435 9276
298 22872
16968 23647
1189 34527
743 22936
37606 18840
9359 23795
27528 36161
33540 23966
24646 29106
14737 38110
20747 2893
18620 12113
25875 32901
37856 13719
21976 1161
34082 16702
4045 9425
7618 9162
31749 38348
34713 23004
13034 13398
20665 12186
17635 29720
10689 30676
36229 10610
1992 37016
116 3408
2264 20768
2599 29618
9799 17450
17236 10259
37259 25909
12102 35449
30578 10479
20481 28330
25752 39534
24469 25577
36845 31311
12059 36263
17595 10131
22561 26391
26981 17973
16198 37476
30328 8136
36539 34811
38063 8846
24610 23083
14469 4360
19881 23333
26076 16774
24617 39979
28097 22117
4037 9916
1437 25948
27226 39335
30779 39774
15895 27662
35975 23023
22503 25384
11663 39665
17271 14898
39569 930
34187 24176
21447 1665
15526 39865
37839 27240
17672 20703
18908 1232
5403 39486
32736 28940
6134 13299
3728 14578
28439 6231
10358 23755
37497 32422
16719 31548
32957 12089
34927 31555
39349 30750
6403 2743
25688 17192
24727 11016
35447 27761
27318 19199
25825 24826
6170 12878
16822 21402
38257 135
18428 29063
25989 18859
31795 5513
7695 38966
1292 1949
15885 10173
12558 19741
28459 36161
10292 29244
28154 19132
9389 30061
9671 23488
20545 18787
21320 38421
37057 38625
1292 30835
26392 16897
36086 14038
1116 8823
1281 30220
26708 37949
8966 10598
34974 4420
21531 14258
9023 4371
9866 31403
37319 38735
26071 35933
11723 38708
22889 5786
1262 26728
6034 18799
14680 22041
8830 4513
18340 27683
15930 11690
4375 12672
4993 31928
7521 16545
2295 14883
36358 26423
25626 2425
26917 8271
2403 36266
9408 20687
22650 13009
22527 4523
16414 37736
3061 34208
24468 10502
24251 34586
8276 31806
26119 28568
728 35952
22820 36393
31489 9250
13323 14236
7989 2157
24250 8087
12551 21353
29932 20090
27247 13760
14573 22920
23246 20020
23024 2424
15278 15617
6779 23964
18845 4689
3082 15027
34248 13185
101 1517
7016 6717
7646 4871
8562 31391
37162 9712
10723 13522
2737 10062
20511 38846
16376 21118
39626 6582
25056 15867
30221 33286
9935 1141
28017 15470
17910 39168
35525 22748
33634 1141
6316 615
26138 6731
36761 27344
36424 38243
25284 6710
13614 2418
34916 22002
6681 27184
27418 867
35374 23451
26419 39277
37200 33036
3791 8783
13897 5250
16759 15268
9230 541
10958 24534
33047 23899
3609 15916
21937 2210
11944 39145
7663 9109
11306 9567
28538 3666
39088 23445
14841 26837
15959 27376
4105 13827
33045 20071
1528 39288
5736 13596
19630 24552
28024 7900
19548 39639
23565 11344
19792 3689
19335 39820
12723 12393
12509 9775
31763 19857
17084 20459
14521 34705
36152 15162
10299 12356
4788 8609
612 9788
33501 22565
3359 38057
435 39248
2362 11171
32543 5094
25691 29537
9093 13647
26309 2160
11508 33678
15614 1383
35701 11367
18741 27997
7304 27012
9730 27976
31248 8475
3735 32185
34355 34467
16373 37669
21635 10566
16188 23449
31139 14555
6167 15564
32806 8575
2529 3579
5166 27700
19375 2360
12888 13958
33323 27037
35208 24154
32658 21556
33054 34844
6338 31214
10034 31928
16745 2323
7620 2282
13776 32722
17063 2313
5983 30030
35565 18317
25204 16236
26335 13144
20614 36265
33473 28892
18466 17141
12904 23584
18046 38800
28199 27314
28417 30749
32128 21319
27785 25270
24880 22658
25343 3277
16785 26814
6618 11
17053 2800
31236 14936
6471 15947
15367 27995
23430 14310
3194 16664
32444 13796
38 20357
16719 10467
39582 31355
31383 5410
16840 435
11260 31182
30660 10943
15502 18794
14617 13414
19833 24622
36491 5224
33659 34948
27827 28540
21631 34135
4884 29326
3268 3512
29250 22737
7640 24555
25387 30569
18158 24113
28591 38427
23240 37443
26130 30860
23838 4840
13259 6604
19335 31931
2595 21530
1942 97
38449 30667
25829 24530
18365 39323
*/
