#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <time.h>



typedef struct node {
  char *s, *l, *f, *j, *m;
} node_t;

static void node_print(const node_t *n) {
  printf("s: %s; l: %s; f: %s; j: %s; m: %s\n", n->s, n->l, n->f, n->j, n->m);
}
//////////////////////////////////////////////////////////////

typedef struct cnode {
  const char *s, *l, *f, *j, *m;
  int s_, l_, f_, j_, m_;
} cnode_t;

static void cnode_print(const cnode_t *n) {
  printf("s: %.*s; l: %.*s; f: %.*s; j: %.*s; m: %.*s\n", n->s_, n->s,
         n->l_, n->l, n->f_, n->f, n->j_, n->j, n->m_, n->m);
}

static node_t node_at_erasing(char *str, int ix) {
  node_t res = {0};
  char *tok_node = NULL;
  char *tok_part = NULL;
  int nc = -1;
  char **dst[5] = {&res.s, &res.l, &res.f, &res.j, &res.m};
  for (; (tok_node = strsep(&str, ";")) != NULL && nc < ix ; ++nc) {
    char ***p_dst = dst;
    for (; (tok_part = strsep(&tok_node, ":")) != NULL; ++p_dst) {
      **p_dst = (*tok_part ? tok_part : **p_dst);
    }
  }

  return res;
}

static cnode_t node_at(const char *str, int ix) {
  cnode_t res = {0};
  char *tok_node, *tok_part;
  int nc = -1;
  const char **dst[5] = {&res.s, &res.l, &res.f, &res.j, &res.m};

  char mask[8] = {';',';',';',';',';',';',';',';'};
  int imask = (*(int*)mask);

  for (; (tok_node = strchr(str, ';')) != NULL && nc < ix; ++nc) {
    const char ***p_dst = dst;
    for (tok_part = strchr(str, ':');
         tok_part != NULL && tok_part < tok_node;
         tok_part = strchr(str, ':'), ++p_dst) {
      if (tok_part - str)
        **p_dst = str;
      str = tok_part + 1;
    }

    if (tok_node - str)
      **p_dst = str;
    str = tok_node+1;

    while ((*(int*)str) == imask && nc < ix) { // todo check somehow that we are not out of string bounds
      str += 8;
      nc += 8;
    }
  }

  int *dst_s[5] = {&res.s_, &res.l_, &res.f_, &res.j_, &res.m_};
  for (int i = 0; i < 5; ++i) {
    if (*dst[i] == NULL) {
      *dst_s[i] = 0;
      continue;
    }
    int l = 0;
    for (; (*dst[i])[l] != ';' && (*dst[i])[l] != ':'; ++l) ;
    *dst_s[i] = l;
  }

  return res;
}

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  const char *src_simple = "1:2:1;:9;2:1:2;;";
  for (int i = 0; i < 5; ++i) {
    cnode_t res = node_at(src_simple, i);
    cnode_print(&res);
  }

  printf("\n\n");
  for (int i = 0; i < 5; ++i) {
    char *srcdup = strdup(src_simple);
    node_t res = node_at_erasing(srcdup, i);
    node_print(&res);
    free(srcdup);
  }

  static const char *tmpl = "559:6070:41:-;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;2444:269;;;;;;:::i;:::-;;:::i;:::-;;5714:481;;;;;;:::i;:::-;;:::i;:::-;;;;;;;:::i;:::-;;;;;;;;4331:343;;;;;;:::i;:::-;;:::i;1533:38::-;;;;;;:::i;:::-;;:::i;:::-;;;;;;;;;;:::i;3702:296::-;;;;;;:::i;:::-;;:::i;2845:280::-;;;;;;:::i;:::-;;:::i;659:24::-;;;:::i;:::-;;;;;;;:::i;3257:280::-;;;;;;:::i;:::-;;:::i;6424:203::-;;;;;;:::i;:::-;;:::i;:::-;;;;;;;:::i;5091:105::-;;;:::i;2444:269::-;2554:10;2567;2597:36;;;;;;;;2567:10;;;;2597:36;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;2567:10;;2597:36;;;;;2624:8;;;;;;2597:36;;2624:8;;;;2597:36;;;;;;;;-1:-1:-1;2597:36:41;;;;-1:-1:-1;;2583:11:41;;;;;;:6;:11;;;;;;;;;:50;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:11;;-1:-1:-1;2583:50:41;;;;;;;;;;;;:::i;:::-;;;;;2670:6;2644:43;;2662:6;2644:43;;2657:3;2644:43;;;2678:8;;2644:43;;;;;;;:::i;:::-;;;;;;;;-1:-1:-1;;2693:10:41;:15;;;;;;2707:1;2693:15;;;;;;;;;-1:-1:-1;;;2444:269:41:o;5714:481::-;5826:10;;5786:14;;5826:10;;;;5816:20;;;;;5808:76;;;;;;;;;;;;:::i;:::-;;;;;;;;;5910:6;5898:18;;:8;:18;;;;5890:62;;;;;;;;;;;;:::i;:::-;5958:24;6006:8;5997:6;:17;5985:30;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:::i;:::-;;;;;;;;;;;;;;;;-1:-1:-1;5958:57:41;-1:-1:-1;6037:8:41;6021:148;6051:6;6047:10;;:1;:10;;;6021:148;;;6098:9;;;;;;;;:6;:9;;;;;;;;;6072:35;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;6098:9;;6072:35;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:9;6086:8;6082:1;:12;6072:23;;;;;;;;;;;;;;;;;;;:35;6059:3;;6021:148;;;-1:-1:-1;6181:9:41;5714:481;-1:-1:-1;;;5714:481:41:o;4331:343::-;4479:11;;;;;;;:6;:11;;;;;:17;;;;;;4465:10;:31;4457:73;;;;;;;;;;;;:::i;:::-;4550:65;;;;;;;;4561:3;4550:65;;;;;;4573:6;4550:65;;;;;;4588:6;4550:65;;;;;;4605:8;;4550:65;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;-1:-1:-1;4550:65:41;;;;-1:-1:-1;;4536:11:41;;;;;;:6;:11;;;;;;;;;:79;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:11;;-1:-1:-1;4536:79:41;;;;;;;;;;;;:::i;:::-;;;;;4652:6;4626:43;;4644:6;4626:43;;4639:3;4626:43;;;4660:8;;4626:43;;;;;;;:::i;:::-;;;;;;;;4331:343;;;;;:::o;1533:38::-;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:::o;3702:296::-;3805:11;;;3783:19;3805:11;;;:6;:11;;;;;3844;;;;;;;3830:10;:25;3822:67;;;;;;;;;;;;:::i;:::-;3895:24;:13;;;3911:8;;3895:24;:::i;:::-;-1:-1:-1;3966:11:41;;;;3953;;3930:63;;3966:11;;;;;3953;;;;;3943:8;;;3930:63;;;;3979:13;;;;3930:63;:::i;:::-;;;;;;;;3702:296;;;;:::o;2845:280::-;2936:11;;;2914:19;2936:11;;;:6;:11;;;;;2975;;;;;;;2961:10;:25;2953:67;;;;;;;;;;;;:::i;:::-;3026:20;;;;;;;;;;;;;;;;;;-1:-1:-1;3093:11:41;;;3057:63;;3093:11;;;;3080;;;;;;;3070:8;;;3057:63;;;;3106:13;;;;3057:63;:::i;:::-;;;;;;;;2845:280;;;:::o;659:24::-;;;;;;:::o;3257:280::-;3348:11;;;3326:19;3348:11;;;:6;:11;;;;;3387;;;;;;;3373:10;:25;3365:67;;;;;;;;;;;;:::i;:::-;3438:11;;;:20;;;;;;;;;;;;;;;;3492:11;;3469:63;;3505:11;;;;3492;;;;;;;3482:8;;;;;3469:63;;;;3518:13;;;;3469:63;:::i;6424:203::-;6480:7;6509:10;;;;;;6503:16;;;;6495:64;;;;;;;;;;;;:::i;:::-;-1:-1:-1;6587:11:41;;;6565:19;6587:11;;;:6;:11;;;;;;;;6611;;;;6424:203;;;;:::o;5091:105::-;5177:1;5180:10;;5138:14;;5167:24;;5180:10;;5167:9;:24::i;:::-;5160:31;;5091:105;:::o;-1:-1:-1:-;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:::i;:::-;;;:::o;:::-;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:::o;:::-;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;14:198;84:20;;144:42;133:54;;123:65;;113:2;;202:1;199;192:12;217:378;;;335:3;328:4;320:6;316:17;312:27;302:2;;360:8;350;343:26;302:2;-1:-1;390:20;;433:18;422:30;;419:2;;;472:8;462;455:26;419:2;516:4;508:6;504:17;492:29;;568:3;561:4;552:6;544;540:19;536:30;533:39;530:2;;;585:1;582;575:12;530:2;292:303;;;;;:::o;600:181::-;669:20;;729:26;718:38;;708:49;;698:2;;771:1;768;761:12;786:585;;;;;952:2;940:9;931:7;927:23;923:32;920:2;;;973:6;965;958:22;920:2;1001:31;1022:9;1001:31;:::i;:::-;991:41;;1051:40;1087:2;1076:9;1072:18;1051:40;:::i;:::-;1041:50;;1142:2;1131:9;1127:18;1114:32;1169:18;1161:6;1158:30;1155:2;;;1206:6;1198;1191:22;1155:2;1250:61;1303:7;1294:6;1283:9;1279:22;1250:61;:::i;:::-;910:461;;;;-1:-1;1330:8;-1:-1;;;;910:461::o;1376:196::-;;1487:2;1475:9;1466:7;1462:23;1458:32;1455:2;;;1508:6;1500;1493:22;1455:2;1536:30;1556:9;1536:30;:::i;:::-;1526:40;1445:127;-1:-1;;;1445:127::o;1577:272::-;;;1705:2;1693:9;1684:7;1680:23;1676:32;1673:2;;;1726:6;1718;1711:22;1673:2;1754:30;1774:9;1754:30;:::i;:::-;1744:40;;1803;1839:2;1828:9;1824:18;1803:40;:::i;:::-;1793:50;;1663:186;;;;;:::o;1854:660::-;;;;;;2036:3;2024:9;2015:7;2011:23;2007:33;2004:2;;;2058:6;2050;2043:22;2004:2;2086:30;2106:9;2086:30;:::i;:::-;2076:40;;2135;2171:2;2160:9;2156:18;2135:40;:::i;:::-;2125:50;;2194:40;2230:2;2219:9;2215:18;2194:40;:::i;:::-;2184:50;;2285:2;2274:9;2270:18;2257:32;2312:18;2304:6;2301:30;2298:2;;;2349:6;2341;2334:22;2298:2;2393:61;2446:7;2437:6;2426:9;2422:22;2393:61;:::i;:::-;1994:520;;;;-1:-1;1994:520;;-1:-1;2473:8;;2367:87;1994:520;-1:-1;;;1994:520::o;2519:507::-;;;;2667:2;2655:9;2646:7;2642:23;2638:32;2635:2;;;2688:6;2680;2673:22;2635:2;2716:30;2736:9;2716:30;:::i;:::-;2706:40;;2797:2;2786:9;2782:18;2769:32;2824:18;2816:6;2813:30;2810:2;;;2861:6;2853;2846:22;2810:2;2905:61;2958:7;2949:6;2938:9;2934:22;2905:61;:::i;:::-;2625:401;;2985:8;;-1:-1;2879:87;;-1:-1;;;;2625:401::o;3031:270::-;;;3158:2;3146:9;3137:7;3133:23;3129:32;3126:2;;;3179:6;3171;3164:22;3126:2;3207:30;3227:9;3207:30;:::i;:::-;3197:40;;3256:39;3291:2;3280:9;3276:18;3256:39;:::i;3306:537::-;;3388:5;3382:12;3415:6;3410:3;3403:19;3440:3;3452:162;3466:6;3463:1;3460:13;3452:162;;;3528:4;3584:13;;;3580:22;;3574:29;3556:11;;;3552:20;;3545:59;3481:12;3452:162;;;3632:6;3629:1;3626:13;3623:2;;;3698:3;3691:4;3682:6;3677:3;3673:16;3669:27;3662:40;3623:2;-1:-1;3757:2;3745:15;3762:66;3741:88;3732:98;;;;3832:4;3728:109;;3358:485;-1:-1;;3358:485::o;3848:226::-;4024:42;4012:55;;;;3994:74;;3982:2;3967:18;;3949:125::o;4079:1419::-;4296:2;4348:21;;;4418:13;;4321:18;;;4440:22;;;4079:1419;;4296:2;4481;;4499:18;;;;4559:15;;;4544:31;;4540:40;;4603:15;;;4079:1419;4649:820;4663:6;4660:1;4657:13;4649:820;;;4728:22;;;4752:66;4724:95;4712:108;;4843:13;;4915:9;;4926:26;4911:42;4896:58;;4993:11;;;4987:18;5028:42;5107:21;;;5090:15;;;5083:46;5176:11;;;5170:18;5166:27;5149:15;;;5142:52;5217:4;5262:11;;;5256:18;4879:4;5294:15;;;5287:27;;;5256:18;5337:52;5373:15;;;5256:18;5337:52;:::i;:::-;5447:12;;;;5327:62;-1:-1;;;5412:15;;;;4685:1;4678:9;4649:820;;;-1:-1;5486:6;;4276:1222;-1:-1;;;;;;;;4276:1222::o;5503:452::-;;5662:2;5651:9;5644:21;5701:6;5696:2;5685:9;5681:18;5674:34;5758:6;5750;5745:2;5734:9;5730:18;5717:48;5785:22;;;5809:2;5781:31;;;5774:45;;;;5871:2;5859:15;;;5876:66;5855:88;5840:104;5836:113;;5634:321;-1:-1;5634:321::o;5960:1037::-;;6098:2;6138;6127:9;6123:18;6168:2;6157:9;6150:21;6191:4;6227:6;6221:13;6253:1;6285:2;6274:9;6270:18;6302:1;6297:236;;;;6547:1;6542:429;;;;6263:708;;6297:236;6356:4;6352:1;6341:9;6337:17;6333:28;6325:6;6318:44;6417:66;6406:9;6402:82;6397:2;6386:9;6382:18;6375:110;6520:2;6509:9;6505:18;6498:25;;6297:236;;6542:429;6592:1;6581:9;6577:17;6622:6;6614;6607:22;6657:39;6689:6;6657:39;:::i;:::-;6718:4;6735:180;6749:6;6746:1;6743:13;6735:180;;;6842:14;;6818:17;;;6837:2;6814:26;6807:50;6885:16;;;;6764:10;;6735:180;;;6939:17;;6958:2;6935:26;;-1:-1;;;6263:708;-1:-1;6988:3;;6078:919;-1:-1;;;;;;;6078:919::o;7002:355::-;7204:2;7186:21;;;7243:2;7223:18;;;7216:30;7282:33;7277:2;7262:18;;7255:61;7348:2;7333:18;;7176:181::o;7362:353::-;7564:2;7546:21;;;7603:2;7583:18;;;7576:30;7642:31;7637:2;7622:18;;7615:59;7706:2;7691:18;;7536:179::o;7720:407::-;7922:2;7904:21;;;7961:2;7941:18;;;7934:30;8000:34;7995:2;7980:18;;7973:62;8071:13;8066:2;8051:18;;8044:41;8117:3;8102:19;;7894:233::o;8132:399::-;8334:2;8316:21;;;8373:2;8353:18;;;8346:30;8412:34;8407:2;8392:18;;8385:62;8483:5;8478:2;8463:18;;8456:33;8521:3;8506:19;;8306:225::o;8536:208::-;8710:26;8698:39;;;;8680:58;;8668:2;8653:18;;8635:109::o;8749:547::-;;8992:26;8984:6;8980:39;8969:9;8962:58;9039:42;9129:2;9121:6;9117:15;9112:2;9101:9;9097:18;9090:43;9181:2;9173:6;9169:15;9164:2;9153:9;9149:18;9142:43;;9221:3;9216:2;9205:9;9201:18;9194:31;9242:48;9285:3;9274:9;9270:19;9262:6;9242:48;:::i;:::-;9234:56;8952:344;-1:-1;;;;;;8952:344::o;9301:129::-;;9369:17;;;9419:4;9403:21;;;9359:71::o;";
  size_t tmpl_len = strlen(tmpl);
  char *src_big = malloc(tmpl_len * 10000);
  for (int i = 0; i < 10000; ++i) {
    strcpy(src_big + tmpl_len*i, tmpl);
  }

  clock_t start, end;
  double cpu_time_used;
  start = clock();
  cnode_t cres = node_at(src_big, 26829999);
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("ro took: %f\n", cpu_time_used);
  cnode_print(&cres);

  start = clock();
  node_t res = node_at_erasing(src_big, 26829999);
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("erasing took: %f\n", cpu_time_used);
  node_print(&res);
  free(src_big);

  return 0;
}
