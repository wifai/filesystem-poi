/* Rakjat Priboemi */
/* File : mount_poi.c */

#include "stdio.h"
#include "stdlib.h"
#include "rp_poi.h"
#include "rp_fuse.h"

FILE * stream;
poi_file filesys;
time_t mount_time;

struct fuse_operations rp_oper;
void init_fuse()
{
  rp_oper.getattr	= rp_poi_getattr;
  rp_oper.readdir	= rp_poi_readdir;
  rp_oper.mkdir	= rp_poi_mkdir;
  rp_oper.open = rp_poi_open;
  rp_oper.rmdir = rp_poi_rmdir;
  rp_oper.rename	= rp_poi_rename;
  rp_oper.unlink	= rp_poi_unlink;
  rp_oper.mknod	= rp_poi_mknod;
  rp_oper.truncate= rp_poi_truncate;
  rp_oper.write	= rp_poi_write;
  rp_oper.read	= rp_poi_read;
  rp_oper.link	= rp_poi_link; 
}
// {
//   .getattr  = rp_poi_getattr,
//   .readdir  = rp_poi_readdir,
//   .mkdir  = rp_poi_mkdir,
//   .open = rp_poi_open,
//   .rmdir = rp_poi_rmdir,
//   .rename = rp_poi_rename,
//   .unlink = rp_poi_unlink,
//   .mknod  = rp_poi_mknod,
//   .truncate= rp_poi_truncate,
//   .write  = rp_poi_write,
//   .read = rp_poi_read,
//   .link = rp_poi_link
// };

int main(int argc, char* argv[]) {
  time(&mount_time);
  if(argc < 3) {
    printf("How to use : ./mount-poi <mount_folder> <filesystem.poi> [-new]\n");
    return 0;
  }
  printf("%d\n", argc);
  if(argc > 3) {
    if(strcmp("-new", argv[3]) == 0) {
      createFilesystem(argv[2]);
    }
  }
  loadFilesystem(argv[2]);
  init_fuse();
  int fargc = 2;
  char* fargv[2] = { argv[0], argv[1] };
  writeVolumeInfo();
  return fuse_main(fargc, fargv, &rp_oper, NULL);
  // return 0;
}