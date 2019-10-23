#include <unistd.h>
#include <stdlib.h>
#include "inc/gsf.h"
#include "bsp.h"

#include "sadp.h"     // discover
#include "upg.h"      // upgrade

GSF_LOG_GLOBAL_INIT("SEARCH", 8*1024);

// route add -net 224.0.0.0 netmask 240.0.0.0 dev ens33
// gcc -g  -o tt  search.c  src/sadp.c -I/mnt/hgfs/works/gsf-20190612/gsf -Isrc -Iinc -L/mnt/hgfs/works/gsf-20190612/gsf/lib/x86 -lnm -lpthread
// export LD_LIBRARY_PATH=../../lib/x86
// ./tt 238.238.238.238


static int sadp_recv_func(gsf_sadp_msg_t *in, gsf_msg_t* out
          , int *osize/*IN&OUT*/, gsf_sadp_peer_t* peer)
{
  int ret = 0;
  
  printf(" <<<< in->ver:%04X, modid:%d, msg.size:%d, peer:[%s:%d]\n"
        , in->ver, in->modid, in->msg.size, peer->ipaddr, peer->port);

  *osize = 0;
  return 0;
}



int main(int argc, char *argv[])
{
  if(argc < 2)
  {
    printf("pls %s 238.238.238.238 || 192.168.1.2 \n", argv[0]);
    return 0;
  }

  gsf_sadp_ini_t puini = {
    .ethname= "ens33",
    .lcaddr = "0.0.0.0",
    .mcaddr = "238.238.238.238",
    .mcport = 8888,
    .cb = sadp_recv_func,
  };
 
  int ret = sadp_pu_init(&puini);
  printf("sadp_pu_init ret:%d\n", ret);


  gsf_sadp_peer_t dst1;
  strcpy(dst1.ipaddr, argv[1]);
  dst1.port = 8888;
  

  gsf_sadp_msg_t in = {.ver = 0x1234, .modid = GSF_MOD_ID_BSP, .msg = {.id = GSF_ID_BSP_DEF}};

  char outbuf[64*1024] = {0};
  gsf_msg_t *out = (gsf_msg_t*)outbuf;
  int osize = sizeof(outbuf);

  gsf_sadp_peer_t *dst = &dst1;
  
  printf("\n >>>> sadp_cu_gset %s %d osize:%d, out->size:%d\n", dst->ipaddr, time(NULL), osize, out->size);
  sadp_cu_gset(dst, &in, out, &osize, 3);
  if(osize > 0)
    printf("\n <<<< sadp_cu_gset %s %d osize:%d, out->size:%d\n", dst->ipaddr, time(NULL), osize, out->size);
  printf("\n\n\n");
  
  return 0;
}
