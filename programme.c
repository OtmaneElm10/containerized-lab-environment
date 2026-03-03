#define _GNU_SOURCE /*Doit etre appele en premier (permet d'acceder a
des appels systemes non normalise: unshare ici) */


#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/mount.h>
#include<unistd.h>
#include<wait.h>
#include<sched.h>
//Attention: doit etre lance en sudo/root
int main()
{
 pid_t retourFork;
 int flags;
 //0. Penser a creer tous les dossiers et copier les binaires et
    //librairies //(se fait en ligne de commande) qui seront chrooter apres
        //(bin, tmp, media, lib, et lib64) 



 //1.
 //Unshare a faire avant le fork pour un nouveau namespace pid.
 //Pour NEWPID seuls les enfants sont dans un nouveau namespace PID -
    //c'est pour cette raison qu'on le fait avant le fork 


    if(unshare(CLONE_NEWPID) == -1) {
        perror("unshare PID");
        exit(EXIT_FAILURE);
    }; 




 //2. Votre processus se fork

    __pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }


 //3.
 //Les autres "unshare" ont lieu apres le fork pour ne pas isoler le
//processus pere (celui-ci peut-etre vu comme le runtime) 



 //4. Le pere attend son fils et affiche son message quand celui-ci
 //est termine: wait().
 //Traiter l'erreur aussi sur le fork.

    if (pid > 0) {
        waitpid(pid, NULL, 0);
        printf("Le fils a termine\n");
        exit(0);
    }





 //5. Le fils: /*
    if(pid == 0){
      if(unshare(CLONE_NEWNS | CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWNET ) == -1){
        perror("unshare");
        exit(EXIT_FAILURE);
      }
    }


    // Empêche la propagation vers le parent
    if (mount(NULL, "/", NULL, MS_REC | MS_SLAVE, NULL) == -1) {
        perror("mount MS_SLAVE");
        exit(EXIT_FAILURE);
    }


    // ---Les differents mounts---

    //mount tmpfs
    if(mount("tmpfs", "/home/otmane/Univ/M1/automne/SystAvancés/TPDOCK1/chroot/tmp", "tmpfs", 0, "") == -1){
        perror("mount tmpfs");
        exit(EXIT_FAILURE); 
    }


    //mount media
    if(mount("/media", "/home/otmane/Univ/M1/automne/SystAvancés/TPDOCK1/chroot/media", NULL, MS_BIND, NULL) == -1) {
        perror("mount media");
        exit(EXIT_FAILURE);
    }

    //mount proc

    if(mount("proc", "/home/otmane/Univ/M1/automne/SystAvancés/TPDOCK1/chroot/proc", "proc", 0, "") == -1){
        perror("mount proc");
        exit(EXIT_FAILURE);
    }

    //chroot

    if(chroot("/home/otmane/Univ/M1/automne/SystAvancés/TPDOCK1/chroot") == -1){
        perror("chroot");
        exit(EXIT_FAILURE);
    }

    chdir("/");




    //lancer la commande bash

    execlp("bash", "bash", NULL); //utilisée pour entrer dans le conteneur

    perror("execlp");
    exit(EXIT_FAILURE);


 return(0);
} 