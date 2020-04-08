# Introduction

The files in this folder will be used to setup an independent build machine
providing full virtualization with help of Vagrant.

Thus having a complete build toolchain from scratch.

# Setup

## Required applications

* ```vagrant``` needs to be installed on your system
* ```ansible``` needs to be installed on your system

By default ```virtualbox``` is configured to be used by ```vagrant``` and needs to be installed.

## Configuration

### TL;DR

```ruby Vagrantfile
SHARED_FOLDER_HOST = "shared/"
SHARED_FOLDER_REMOTE = "/opt/vip"
```

Need to ```mkdir $SHARED_FOLDER_HOST``` locally.
Goto **Run**

### Shared Folder
The Source and build will be available on the host machine within a shared folder.

#### Host machine, this directory

Will be ```./shared``` by default.

* Choose a shared folder on your host machine, e.g. ```shared/```
* ```mkdir shared``` in this folder
* Review configuration in Vagrantfile: ```SHARED_FOLDER_HOST```

#### Virtual build machine, provisioned with ansible

Will be ```/opt/vip``` by default.

* Review configuration in Vagrantfile: ```SHARED_FOLDER_REMOTE```

# Run

**beware compiling may take a long time!**

This follows basic vagrant workflow, e.g.

* ```vagrant up --provision``` loads box and force-executes ansible provison
* ```ls shared``` provides access to the build-folder within the virtual build machine
* ```vagrant ssh``` ssh into the virtual build machine

# Standalone provisioning

With only ```ansible``` installed, it is possible to configure a **Ubuntu 16.04** remote server to compile and run the vip.

Do not forget to change **server_ip** and username. Expects to connect to your remote VPS via SSH and password-auth.
Consult manpage of ```ansible-playbook``` for other options.

```shell
ansible-playbook provision.yml -i "sever_ip," --extra-vars '{"shared_folder_remote":"/opt/vip"}' -u sudouser -k
```

*shared_folder_remote* will be the target for vip git repo and compile action.

