#include "globaluti.h"

//
// Created by song on 3/1/18.
//
void mycreat(char* path)
{
//    formalizecmdline(path);
    char dirname[16];
    chararrayclear(dirname,16);
    int begin=0;
    for(begin=strlen(path)-3;((path[begin]!=' ')&&(path[begin]!='/')&&(begin>0));begin--);
    int cur=0;
    int recordbegin=begin;
    begin++;
    for(;begin<strlen(path)-2;begin++)
    {
        dirname[cur++]=path[begin];
    }
    struct TreeNode* curnode=root;
    if(path[1]=='/')
    {
        int i=1;
        int flag=0;
        while(1)
        {
            char tmpname[16];
            chararrayclear(tmpname,16);
            int j;
            for(j=i+1;;j++)
            {
                if(path[j]=='$')
                {
                    return;
                }
                if(path[j]=='/')
                {
                    break;
                }
                tmpname[j-i-1]=path[j];
            }
            if((strcmp(tmpname,dirname)==0)&&(recordbegin==i))
            {
                struct TreeNode* newnode=(struct TreeNode*)malloc(sizeof(struct TreeNode));
                strcpy(newnode->name,dirname);
                newnode->father=curnode;
                newnode->type=0;
                newnode->ChildNum=0;
                for(int k=0;k<10;k++)
                {
                    if(curnode->childlist[k]==NULL)
                    {
                        curnode->childlist[k]=newnode;
                        break;
                    }
                }
                curnode->ChildNum++;
                newnode->father=curnode;
                freeinodenum=computeinodenum();
                curnode->inodenum=freeinodenum;
                freenode[freeinodenum]=1;
                struct inode newinode;
                newinode.length=0;
                newinode.type=0;
                newinode.storetype=-1;
                int *res=allocblocks(8);
                for(int i=0;i<8;i++)
                {
                    newinode.i_addr[i]=res[i];
                }
                fseek(fp,20*512+freeinodenum*sizeof(struct inode),SEEK_SET);
                fwrite(&newinode,sizeof(struct inode),1,fp);
                return;
            }
            i=j;
            flag=0;
            for(int k=0;k<curnode->ChildNum;k++)
            {
                if(strcmp(curnode->childlist[k]->name,tmpname)==0)
                {
                    flag=1;
                    curnode=curnode->childlist[k];
                    if(curnode->type==0)
                    {
                        printf("Invalid Path\n");
                        return ;
                    }
                    break;
                }
            }
            if(flag==0)
            {
                printf("The file doesn't exist!\n");
                return;
            }
        }
    }
    else
    {
        struct TreeNode* curnode=globalcurnode;
        int i=0;
        int flag=0;
        while(1)
        {
            char tmpname[16];
            chararrayclear(tmpname,16);
            int j;
            for(j=i+1;;j++)
            {
                if(path[j]=='$')
                {
                    return;
                }
                if(path[j]=='/')
                {
                    break;
                }
                tmpname[j-i-1]=path[j];
            }
            if((strcmp(tmpname,dirname)==0)&&(recordbegin==i))
            {
                struct TreeNode* newnode=(struct TreeNode*)malloc(sizeof(struct TreeNode));
                strcpy(newnode->name,dirname);
                newnode->father=curnode;
                newnode->type=0;
                newnode->ChildNum=0;
                for(int k=0;k<10;k++)
                {
                    if(curnode->childlist[k]==NULL)
                    {
                        curnode->childlist[k]=newnode;
                        break;
                    }
                }
                curnode->ChildNum++;
                newnode->father=curnode;
                freeinodenum=computeinodenum();
                curnode->inodenum=freeinodenum;
                freenode[freeinodenum]=1;
                struct inode newinode;
                newinode.length=0;
                int *res=allocblocks(8);
                for(int i=0;i<8;i++)
                {
                    newinode.i_addr[i]=res[i];
                }
                newinode.type=0;
                newinode.storetype=-1;
                int r=fseek(fp,20*512+freeinodenum*sizeof(struct inode),SEEK_SET);
                int offset=ftell(fp);
                int len=fwrite(&newinode,sizeof(struct inode),1,fp);

                int errornum=ferror(fp);

//                int rr=fseek(fp,512*20+(curnode->inodenum)*sizeof(struct inode),SEEK_SET);
//                long off=ftell(fp);
//                len=fread(&newinode,sizeof(struct inode),1,fp);
//
//                errornum=ferror(fp);
                return;
            }
            i=j;
            flag=0;
            for(int k=0;k<curnode->ChildNum;k++)
            {
                if(strcmp(curnode->childlist[k]->name,tmpname)==0)
                {
                    flag=1;
                    curnode=curnode->childlist[k];
                    if(curnode->childlist[k]->type==0)
                    {
                        printf("Invalid Path\n");
                        return ;
                    }
                    break;
                }
            }
            if(flag==0)
            {
                printf("The file doesn't exist!\n");
                return;
            }
        }
    }
}
int myopen(char* path,int mode)
{
//    formalizecmdline(path);
    char filename[16];
    int begin=0;
    for(begin=strlen(path)-3;((path[begin]!='/')&&(begin>0)&&(path[begin]!=' '));begin--);
    int cur=0;
    int recordbegin=begin;
    begin++;
    for(;begin<strlen(path)-2;begin++)
    {
        filename[cur++]=path[begin];
    }
    struct TreeNode* curnode=root;
    int i=1;
    int flag=0;
    while(1)
    {
        char tmpname[16];
        chararrayclear(tmpname,16);
        int j;
        for(j=i+1;;j++)
        {
            if(path[j]=='$')
            {

            }
            if(path[j]=='/')
            {
                break;
            }
            tmpname[j-i-1]=path[j];
        }
        if((strcmp(tmpname,filename)==0)&&(recordbegin==i))
        {
            for(int k=0;k<curnode->ChildNum;k++)
            {
                if(strcmp(curnode->childlist[k]->name,tmpname)==0)
                {
                    flag=1;
                    curnode=curnode->childlist[k];
//                    if(curnode->type==0)
//                    {
//                        printf("Invalid Path\n");
//                        return -1;
//                    }
//                    break;
                }
            }
            if(flag==0)
            {
//                printf("The file doesn't exist!\n");
                return -1;
            }
            if(mode==1)
            {
                curnode->statue=1;
                struct inode newinode;
                fseek(fp,512*20+(curnode->inodenum)*sizeof(struct inode),SEEK_SET);
                fread(&newinode,sizeof(struct inode),1,fp);
                struct  activeinode *newactiveinode=(struct activeinode*)malloc(sizeof(struct activeinode));
                newactiveinode->inodenum=curnode->inodenum;
                newactiveinode->type=1;
                for(int i=0;i<8;i++)
                {
                    newactiveinode->i_addr[i]=newinode.i_addr[i];
                }
                newactiveinode->length=newinode.length;
                newactiveinode->refcount=1;
                int fd=computefreesheetnum();
                curnode->filedescriptor=fd;
                curnode->statue=1;
                freesystemopenfilesheet[fd]=1;
                u_ofile[fd]=(struct systemopenfilesheet*)malloc(sizeof(struct systemopenfilesheet));
                u_ofile[fd]->offset=0;
                u_ofile[fd]->ptrtoactiveinode=newactiveinode;
                u_ofile[fd]->refcount=1;
                u_ofile[fd]->ptrtotreenode=curnode;
                return fd;
            }
            else
            {
                free(u_ofile[curnode->filedescriptor]->ptrtoactiveinode);
                free(u_ofile[curnode->filedescriptor]);
                freesystemopenfilesheet[curnode->filedescriptor]=0;
                struct inode newinode;
                fseek(fp,SEEK_SET,512*20+(curnode->inodenum)*sizeof(struct inode));
                fread(&newinode,sizeof(struct inode),1,fp);
                freeblocks(newinode.i_addr);
                free(curnode);
                for(int k=0;k<curnode->father->ChildNum;k++)
                {
                    if(strcmp(curnode->father->childlist[k]->name,tmpname)==0)
                    {
                        curnode->father->childlist[k]=NULL;
                    }
                }
                (curnode->father->ChildNum)-1;
                freenode[curnode->inodenum]=1;
                free(curnode);
            }
        }
        i=j;
        flag=0;
        for(int k=0;k<curnode->ChildNum;k++)
        {
            if(strcmp(curnode->childlist[k]->name,tmpname)==0)
            {
                flag=1;
                curnode=curnode->childlist[k];
                if(curnode->childlist[k]->type==0)
                {
                    printf("Invalid Path\n");
                    return -1;
                }
                break;
            }
        }
        if(flag==0)
        {
//            printf("The file doesn't exist!\n");
            return -1;
        }
    }

}

int myclose(int fd)
{
    if(freesystemopenfilesheet[fd]==0)
        return 0;
    freesystemopenfilesheet[fd]=0;
    u_ofile[fd]->ptrtotreenode->statue=0;
    struct inode newinode;
    newinode.length=u_ofile[fd]->ptrtoactiveinode->length;
    for(int i=0;i<8;i++)
    {
        newinode.i_addr[i]=u_ofile[fd]->ptrtoactiveinode->i_addr[i];
    }
    fseek(fp,SEEK_SET,30*512+u_ofile[fd]->ptrtotreenode->inodenum*512);
    fwrite(&newinode,sizeof(struct inode),1,fp);
    free(u_ofile[fd]->ptrtoactiveinode);
    free(u_ofile[fd]);

    return 1;
}
int mywrite(int fd, char *buf,int bytes)
{
    for(int i=0;i<100;i++)
    {
        printf("%c",buf[i]);
    }
    printf("\n");
    if(u_ofile[fd]->ptrtotreenode->statue==0)
    {
        return -1;//the file must be opend;
    }
    int curoff=u_ofile[fd]->offset;
    int offplusbytes=u_ofile[fd]->offset+bytes;
    int offblocknum=(curoff)/512;
    int offrem=curoff-curoff/512*512;
    int offplusbytesnum=(offplusbytes)/512;
    int offplusbytesrem=offplusbytes-offplusbytes/512*512;
    int *i_addr=u_ofile[fd]->ptrtoactiveinode->i_addr;
    if(offblocknum==offplusbytesnum)
    {
        fseek(fp,20*512+512*i_addr[offblocknum],SEEK_SET);
        fwrite(buf,1,offplusbytes-curoff,fp);
        return ;
    }
    int blocks=offplusbytesnum-offblocknum;
    if((offrem==0)&&(offplusbytesrem==0))
    {
        for(int i=offblocknum;i<offplusbytesnum;i++)
        {
            fseek(fp,30*512+i_addr[i]*512,SEEK_SET);
            fwrite(buf+512*(i-offblocknum),sizeof(char),512,fp);
        }
    }
    else if((offrem==0)&&(offplusbytesrem!=0))
    {
        int i;
        for(i=offblocknum;i<offplusbytesnum;i++)
        {
            fseek(fp,30*512+((long)i_addr[i])*512,SEEK_SET);
            int offset=ftell(fp);
            fwrite(buf+512*(i-offblocknum),sizeof(char),512,fp);
        }
        fseek(fp,30*512+i_addr[offplusbytesnum]*512,SEEK_SET);
        fwrite(buf+512*(i-offblocknum),sizeof(char),offplusbytesrem,fp);
    }
    else if((offrem!=0)&&(offplusbytesrem==0))
    {
        fseek(fp,30*512+i_addr[offblocknum]*512+offrem,SEEK_SET);
        fwrite(buf,sizeof(char),512-offrem,fp);
        int i;
        for(i=offblocknum+1;i<offplusbytesnum;i++)
        {
            fseek(fp,30*512+i_addr[i]*512,SEEK_SET);
            fwrite(buf+512*(i-offblocknum)+512-offrem,sizeof(char),512,fp);
        }
    }
    else
    {
        fseek(fp,30*512+i_addr[offblocknum]*512+offrem,SEEK_SET);
        fwrite(buf,sizeof(char),512-offrem,fp);
        int i;
        for(i=offblocknum+1;i<offplusbytesnum;i++)
        {
            fseek(fp,30*512+i_addr[i]*512,SEEK_SET);
            fwrite(buf+512*(i-offblocknum)+512-offrem,sizeof(char),512,fp);
        }
        fseek(fp,30*512+i_addr[offplusbytesnum]*512,SEEK_SET);
        fwrite(buf+512*(i-offblocknum)+512-offrem,sizeof(char),offplusbytesrem,fp);
    }
    return 1;
}
int seek(int fd,int mode,int bytes)
{
    if(u_ofile[fd]->ptrtotreenode->statue==0)
    {
        return -1;//the file must be opend;
    }
    if(mode==0)
    {
        u_ofile[fd]->offset=bytes;
    }
    u_ofile[fd]->offset+=bytes;
}
int myread(int fd,char * buf,int bytes)
{
    if(u_ofile[fd]->ptrtotreenode->statue==0)
    {
        return -1;//the file must be opend;
    }
    int curoff=u_ofile[fd]->offset;
    int offplusbytes=u_ofile[fd]->offset+bytes;
    int offblocknum=(curoff)/512;
    int offrem=curoff-curoff/512*512;
    int offplusbytesnum=(offplusbytes)/512;
    int offplusbytesrem=offplusbytes-offplusbytes/512*512;
    int *i_addr=u_ofile[fd]->ptrtoactiveinode->i_addr;
    if(offblocknum==offplusbytesnum)
    {
        fseek(fp,20*512+512*i_addr[offblocknum],SEEK_SET);
        fread(buf,1,offplusbytes-curoff,fp);
        return ;
    }
    int blocks=offplusbytesnum-offblocknum;
    if((offrem==0)&&(offplusbytesrem==0))
    {
        for(int i=offblocknum;i<offplusbytesnum;i++)
        {
            fseek(fp,30*512+i_addr[i]*512,SEEK_SET);
            fread(buf+512*(i-offblocknum),sizeof(char),512,fp);
        }
    }
    else if((offrem==0)&&(offplusbytesrem!=0))
    {
        int i;
        for(i=offblocknum;i<offplusbytesnum;i++)
        {
            fseek(fp,30*512+i_addr[i]*512,SEEK_SET);
            fread(buf+512*(i-offblocknum),sizeof(char),512,fp);
        }
        fseek(fp,30*512+i_addr[offplusbytesnum]*512,SEEK_SET);
        fread(buf+512*(i-offblocknum),sizeof(char),offplusbytesrem,fp);
    }
    else if((offrem!=0)&&(offplusbytesrem==0))
    {
        fseek(fp,30*512+i_addr[offblocknum]*512+offrem,SEEK_SET);
        fread(buf,sizeof(char),512-offrem,fp);
        int i;
        for(i=offblocknum+1;i<offplusbytesnum;i++)
        {
            fseek(fp,30*512+i_addr[i]*512,SEEK_SET);
            fread(buf+512*(i-offblocknum)+512-offrem,sizeof(char),512,fp);
        }
    }
    else
    {
        fseek(fp,30*512+i_addr[offblocknum]*512+offrem,SEEK_SET);
        fread(buf,sizeof(char),512-offrem,fp);
        int i;
        for(i=offblocknum+1;i<offplusbytesnum;i++)
        {
            fseek(fp,30*512+i_addr[i]*512,SEEK_SET);
            fread(buf+512*(i-offblocknum)+512-offrem,sizeof(char),512,fp);
        }
        fseek(fp,30*512+i_addr[offplusbytesnum]*512,SEEK_SET);
        fread(buf+512*(i-offblocknum)+512-offrem,sizeof(char),offplusbytesrem,fp);
    }
    for(int i=0;i<100;i++)
    {
        printf("%c",buf[i]);
    }
    printf("\n");
    return 1;
}
int fremove(char *path)
{
    formalizecmdline(path);
    char dirname[16];
    int begin=0;
    for(begin=strlen(path)-1;((path[begin]!='/')&&(begin>0));begin--);
    int cur=0;
    int recordbegin=begin;
    begin++;
    for(;begin<strlen(path)-2;begin++)
    {
        dirname[cur++]=path[begin];
    }
    struct TreeNode* curnode=root;
    int i=1;
    int flag=0;
    while(1)
    {
        char tmpname[16];
        chararrayclear(tmpname,16);
        int j;
        for(j=i+1;;j++)
        {
            if(path[j]=='$')
            {
                return;
            }
            if(path[j]=='/')
            {
                break;
            }
            tmpname[j-i-1]=path[j];
        }
        if((strcmp(tmpname,dirname)==0)&&(recordbegin==i))
        {

        }
        i=j;
        flag=0;
        for(int k=0;k<curnode->ChildNum;k++)
        {
            if(strcmp(curnode->childlist[k]->name,tmpname)==0)
            {
                flag=1;
                curnode=curnode->childlist[k];
                if(curnode->childlist[k]->type==0)
                {
                    printf("Invalid Path\n");
                    return ;
                }
                break;
            }
        }
        if(flag==0)
        {
            printf("The file doesn't exist!\n");
            return;
        }
    }
}
int dirdelete(struct TreeNode** ptrtocurnode)
{
    struct TreeNode * curnode=*ptrtocurnode;
    if(curnode==NULL)
        return 1;
    for(int i=0;i<MAXCHILDNUM;i++)
    {
        if((curnode)->childlist[i]==NULL)
        {
            continue;
        }
        if((curnode)->childlist[i]->type==0)
        {
            freenode[(curnode)->childlist[i]->inodenum]=1;
            dirdelete(&(curnode->childlist[i]));
            free(curnode->childlist[i]);
        }
        else
        {
            curnode->childlist[i]=NULL;
            filedelete(&(curnode->childlist[i]));
        }
    }
    free(curnode);
}
int filedelete(struct TreeNode** ptrtocurnode)
{
    struct TreeNode* curnode=*ptrtocurnode;
    if(curnode==NULL)
        return -1;
    struct inode newinode;
    int res=fseek(fp,512*20+(curnode->inodenum)*sizeof(struct inode),SEEK_SET);
    long offset=ftell(fp);
    fread(&newinode,sizeof(struct inode),1,fp);
    freeblocks(newinode.i_addr);
    free(curnode);
}
