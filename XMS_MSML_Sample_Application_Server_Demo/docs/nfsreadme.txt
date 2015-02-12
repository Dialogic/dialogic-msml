###############################################################################
##
## Copyright © 2006-2012 Dialogic Inc. All Rights Reserved.
##
## The source code contained or described herein and all documents related to
## the source code (collectively "Material") are owned by Dialogic Inc.,
## its subsidiaries, affiliates, suppliers, licensors and/or assigns 
## ("Dialogic"). Title to the Material remains with Dialogic. The Material 
## contains proprietary information and material of Dialogic. The Material is 
## protected by worldwide copyright, trade secret laws, treaty provisions 
## and/or other applicable intellectual property rights, laws and/or treaties.
## No part of the Material may be used, copied, reproduced, modified, 
## published, uploaded, posted, transmitted, distributed, or disclosed in any 
## way without Dialogic's prior express written permission.
##
## No license under any patent, copyright, trade secret or other intellectual
## property right is granted to or conferred upon you by disclosure or delivery
## of the Material, either expressly, by implication, inducement, estoppels
## or otherwise. Any license under such intellectual property rights must be
## express and approved by Dialogic in writing.
##
###############################################################################
# nfsreadme.txt - NFS Installation and Configuration Notes
###############################################################################

The following notes are for setting up NFS v4.0 on CentOS for deploying the MSML
Sample Application Server (app_server) with Dialogic(C) PowerMedia(TM) Extended
Media Server.

Example assumes that PowerMedia XMS is at IP Address 146.152.126.25 and 
app_server is at 146.152.126.48.

On PowerMedia XMS (CentOS), install and configure NFS to export the MSML Sample
Application Server (app_server) media directory:

	1. Add a yum repository to obtain the NFS packages.

		# vi /etc/yum.repos.d/CentOS-Base.repo

		Add:
			# CentOS-Base.repo
			#
			# The mirror system uses the connecting IP address of the client and the
			# update status of each mirror to pick mirrors that are updated to and
			# geographically close to the client.  You should use this for CentOS updates
			# unless you are manually picking other mirrors.
			#
			# If the mirrorlist= does not work for you, as a fall back you can try the 
			# remarked out baseurl= line instead.
			#
			#

			[base]
			name=CentOS-$releasever - Base
			mirrorlist=http://mirrorlist.centos.org/?release=$releasever&arch=$basearch&repo=os
			#baseurl=http://mirror.centos.org/centos/$releasever/os/$basearch/
			gpgcheck=1
			gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS-6
			
			#released updates 
			[updates]
			name=CentOS-$releasever - Updates
			mirrorlist=http://mirrorlist.centos.org/?release=$releasever&arch=$basearch&repo=updates
			#baseurl=http://mirror.centos.org/centos/$releasever/updates/$basearch/
			gpgcheck=1
			gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS-6

			#additional packages that may be useful
			[extras]
			name=CentOS-$releasever - Extras
			mirrorlist=http://mirrorlist.centos.org/?release=$releasever&arch=$basearch&repo=extras
			#baseurl=http://mirror.centos.org/centos/$releasever/extras/$basearch/
			gpgcheck=1
			gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS-6

			#additional packages that extend functionality of existing packages
			[centosplus]
			name=CentOS-$releasever - Plus
			mirrorlist=http://mirrorlist.centos.org/?release=$releasever&arch=$basearch&repo=centosplus
			#baseurl=http://mirror.centos.org/centos/$releasever/centosplus/$basearch/
			gpgcheck=1
			enabled=0
			gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS-6

			#contrib - packages by Centos Users
			[contrib]
			name=CentOS-$releasever - Contrib
			mirrorlist=http://mirrorlist.centos.org/?release=$releasever&arch=$basearch&repo=contrib
			#baseurl=http://mirror.centos.org/centos/$releasever/contrib/$basearch/
			gpgcheck=1
			enabled=0
			gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS-6

	2. Install and configure the NFS packages.

		# yum install nfs-utils nfs4-acl-tools portmap
		
		# vi /etc/exports

			Add: /var/lib/xms/media/en-US/msml 146.152.126.25(rw,sync,no_root_squash,fsid=0)

		# chkconfig nfs on
		
		# chkconfig rpcbind on
		
		# service rpcbind start 
		
		# service nfs start
		
		# vi /etc/sysconfig/iptables

			Add: -A INPUT -s 146.152.126.25 -m state --state NEW -p tcp --dport 2049 -j ACCEPT

		# service iptables restart
		
		# vi /etc/hosts.deny

			Add: portmap:ALL

		# vi /etc/hosts.allow

			Add: portmap: 146.152.126.25

On the MSML application server (NFS Client), mount the export:

		# mkdir /xms

		# mount -t nfs4 146.152.126.48:/ /xms/
		
		# df -H

On the MSML application server, set the app_server configuration to use the 
newly mounted directory:

	# vi <> app_server.cfg

		Set:  mediafilemap:/xms

Reference: http://www.cyberciti.biz/faq/centos-fedora-rhel-nfs-v4-configuration/
