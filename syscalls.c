#include "globaluti.h"

//
// Created by song on 3/1/18.
//
void creat(char* path)
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
                intarrayclear(newinode.i_addr,8);
                fseek(fp,SEEK_SET,30*512+freeinodenum*sizeof(struct inode));
                fwrite(&newinode,sizeof(newinode),1,fp);
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
                newinode.type=0;
                newinode.storetype=-1;
                intarrayclear(newinode.i_addr,8);
                fseek(fp,SEEK_SET,30*512+freeinodenum*sizeof(struct inode));
                fwrite(&newinode,sizeof(newinode),1,fp);
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
int open(char* path,int mode)
{
    formalizecmdline(path);
    char filename[16];
    int begin=0;
    for(begin=strlen(path)-1;((path[begin]!='/')&&(begin>0));begin--);
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
                printf("The file doesn't exist!\n");
                return -1;
            }
            if(mode==1)
            {
                curnode->statue=1;
                struct inode newinode;
                fseek(fp,SEEK_SET,512*20+(curnode->inodenum)*sizeof(struct inode));
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
                u_ofile[fd]->ptrtoactiveinode->i_addr[0]=-1;
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
            printf("The file doesn't exist!\n");
            return -1;
        }
    }

}

int close(int fd)
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
int write(int fd,void *buf,int bytes)
{
    if(u_ofile[fd]->ptrtotreenode->statue==0)
    {
        return -1;//the file must be opend;
    }
    int curoff=u_ofile[fd]->offset;
    int curlen=u_ofile[fd]->ptrtoactiveinode->length;
    int offblocknum=0;
    int offplusbytesnum=0;
    if(curoff+bytes<=curlen)
    {
        offblocknum=curoff/512;
        offplusbytesnum=(curoff+bytes)/512;
        for(int i=offblocknum;i<=offplusbytesnum;i++)
        {
            if(i==offblocknum)
            {
                int start=u_ofile[fd]->ptrtoactiveinode->i_addr[offblocknum];
                fseek(fp,SEEK_SET,30*512+start*512+curoff-(curoff%512)*512);
                fwrite(buf, sizeof(char),512-curoff+(curoff%512)*512,fp);
            }
            else if(i==offplusbytesnum)
            {
                if((curoff+bytes)%512==0)
                {
                    break;
                }
                int end=u_ofile[fd]->ptrtoactiveinode->i_addr[offplusbytesnum];
                fseek(fp,SEEK_SET,30*512+end*512);
                fwrite(buf+512*(offplusbytesnum-offblocknum)+512-curoff+(curoff%512)*512, sizeof(char),curoff+bytes-(curoff+bytes)/512*512,fp);
            }
            fseek(fp,SEEK_SET,30*512+i*512);
            fwrite(buf+512-curoff+(curoff%512)*512+i*512, sizeof(char),512,fp);
        }
    }
    else
    {
        //before curlen
        offblocknum=curoff/512;
        offplusbytesnum=curlen/512;
        int flag=curlen%512;
        for(int i=offblocknum;i<=offplusbytesnum;i++)
        {
            if(i==offblocknum)
            {
                int start=u_ofile[fd]->ptrtoactiveinode->i_addr[offblocknum];
                fseek(fp,SEEK_SET,30*512+start*512+curoff-(curoff%512)*512);
                fwrite(buf, sizeof(char),512-curoff+(curoff%512)*512,fp);
            }
            else if(i==offplusbytesnum)
            {
                if((curoff+bytes)%512==0)
                {
                    break;
                }
                int end=u_ofile[fd]->ptrtoactiveinode->i_addr[offplusbytesnum];
                fseek(fp,SEEK_SET,30*512+end*512);
                fwrite(buf+512*(offplusbytesnum-offblocknum)+512-curoff+(curoff%512)*512,sizeof(char),curoff+bytes-(curoff+bytes)/512*512,fp);
            }
            fseek(fp,SEEK_SET,30*512+i*512);
            fwrite(buf+512-curoff+(curoff%512)*512+i*512, sizeof(char),512,fp);
        }
        //after curlen
        int curblocknum=curlen/512;
        int currem=curlen-curlen/512*512;
        int newblocknum=(curlen+bytes)/512;
        int newrem=curlen+bytes-(curlen+bytes)/512*512;
        int offblocknum=curoff/512;
        int offrem=curoff-curoff/512*512;
        int newallocblocks=newblocknum-curblocknum;
        int* newblocks=allocblocks(newallocblocks);
        if(newallocblocks==0)
        {
            fseek(fp,SEEK_SET,(30+u_ofile[fd]->ptrtoactiveinode->i_addr[curblocknum])*512+currem);
            fwrite(buf+curoff+bytes-curlen,sizeof(char),curoff+bytes-curlen,fp);
        }
        else
        {
            if(currem!=0)
            {
                fseek(fp,SEEK_SET,(30+u_ofile[fd]->ptrtoactiveinode->i_addr[curblocknum])*512+currem);
                fwrite(buf+curoff+bytes-curlen,sizeof(char),512-currem,fp);
            }
            for(int i=0;i<newallocblocks;i++)
            {
                if(currem==0)
                {
                    if(i!=newallocblocks-1)
                    {
                        u_ofile[fd]->ptrtoactiveinode->i_addr[i+curblocknum]=newblocks[i];
                        fseek(fp,SEEK_SET,30*512+newblocks[i]*512);
                        fwrite(buf+curlen-curoff+i*512,sizeof(char),512,fp);
                    }
                    else
                    {
                        u_ofile[fd]->ptrtoactiveinode->i_addr[i+curblocknum]=newblocks[i];
                        fseek(fp,SEEK_SET,30*512+newblocks[i]*512);
                        fwrite(buf+curlen+bytes-(curlen+bytes)/512*512,sizeof(char),512,fp);
                    }
                }
                else
                {
                    if(i!=newallocblocks-1)
                    {
                        u_ofile[fd]->ptrtoactiveinode->i_addr[i+curblocknum]=newblocks[i];
                        fseek(fp,SEEK_SET,30*512+newblocks[i]*512);
                        fwrite(buf+curlen-curoff+512-currem+i*512,sizeof(char),512,fp);
                    }
                    else
                    {
                        u_ofile[fd]->ptrtoactiveinode->i_addr[i+curblocknum]=newblocks[i];
                        fseek(fp,SEEK_SET,30*512+newblocks[i]*512);
                        fwrite(buf+curlen+bytes-(curlen+bytes)/512*512,sizeof(char),512,fp);
                    }
                }
            }
        }

    }
    u_ofile[fd]->offset+=bytes;
    u_ofile[fd]->ptrtoactiveinode->length=curoff+bytes;
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
int read(int fd,void* buf,int bytes)
{
    if(u_ofile[fd]->ptrtotreenode->statue==0)
    {
        return -1;//the file must be opend;
    }
    int curlen=u_ofile[fd]->offset+bytes;
    int curoff=u_ofile[fd]->offset;
    int curnode=(u_ofile[fd]->ptrtoactiveinode->length>1)?(u_ofile[fd]->ptrtoactiveinode->length-1)/512:0;
    int currem=u_ofile[fd]->ptrtoactiveinode->length-curnode*512;
    int offnode=(u_ofile[fd]->offset>1)?(u_ofile[fd]->offset-1)/512:0;
    int offrem=u_ofile[fd]->offset-512*offnode;
    if(curnode==offnode)
    {
        fseek(fp,SEEK_SET,(curnode+30)*512+currem);
        fread(buf,sizeof(char),currem-offrem,fp);
    }
    else
    {
        fseek(fp,SEEK_SET,(curnode+30)*512+currem);
        fwrite(buf,sizeof(char),512-currem,fp);
        int nodes=curnode-offnode;
        for(int i=0;i<nodes;i++)
        {
            if(i==nodes-1)
            {
                fseek(fp,SEEK_SET,(curnode+30)*512+currem);
                fread(buf,sizeof(char),currem-offrem,fp);
            }
            else
            {
                fseek(fp,SEEK_SET,(offnode+i+1+30)*512);
                fread(buf,sizeof(char),512,fp);
            }
        }
    }
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
    fseek(fp,SEEK_SET,512*20+(curnode->inodenum)*sizeof(struct inode));
    fread(&newinode,sizeof(struct inode),1,fp);
    freeblocks(newinode.i_addr);
    free(curnode);
}
