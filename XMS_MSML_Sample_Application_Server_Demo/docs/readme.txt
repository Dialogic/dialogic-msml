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
# readme.txt
###############################################################################
MSML Remote Media Control Application Server Sample Application Readme

Table of Contents:

    1.0 Introduction
    2.0 System Requirements
    3.0 Installation and Configuration
    4.0 Operation
    5.0 Building the application
    6.0 Distribution Contents

1.0 Introduction

The Remote Media Control Application Server Sample Application provides a means 
to demonstrate and exercise features of an MSML Media Sever as supported on 
Dialogic(C) PowerMedia(TM) Extended Media Server.  The Remote control of a Media 
Server by an application server is accomplished by using the SIP based Media 
Server Markup Language (MSML) protocol. Additionally, the sample application is 
intended to demonstrate best known methods (BKM) for software architecture, 
design and API usage.

Typical interaction between a SIP Phone (SIP UA), application server and media 
server:

|--------------|            |------------|          |--------------|
|    SIP UA    |            | app server |          | media server |
|--------------|            |------------|          |--------------|
       |                          |                         |
       |  INVITE (UA SDP)         |                         |
       |------------------------->|  INVITE (UA SDP)        |
       |                          |------------------------>|
       |                          |            180 RINGING  |
       |                          |<------------------------|
       |             180 RINGING  |                         |
       |<-------------------------|                         |
       |                          |        200 OK (MS SDP)  |
       |                          |<------------------------|
       |         200 OK (MS SDP)  |                         |
       |<-------------------------|                         |
       |  ACK                     |                         |
       |------------------------->|                         |
       |                          |  ACK                    |
       |                          |------------------------>|
       |                      RTP started                   |
       |<<================================================>>|
       |                     /    |  INFO <dialigstart>     |
       |                    |     |------------------------>|
       |                    |     |                 200 OK  |
       |                    |     |<------------------------|
       |                    |     |     INFO <dtmf.digits>  |
       |    first dialog   <      |<------------------------|
       |                    |     |  200 OK                 |
       |                    |     |------------------------>|
       |                    |     |     INFO <dialog.exit>  |
       |                    |     |<------------------------|
       |                    |     |  200 OK                 |
       |                     \    |------------------------>|
       |                     /    |  INFO <dialigstart>     |
       |                    |     |------------------------>|
       |                    |     |                 200 OK  |
       |                    |     |<------------------------|
       |                    |     |     INFO <dtmf.digits>  |
       |    second dialog  <      |<------------------------|
       |    chosen based    |     |  200 OK                 |
       |    on dtmf.digits  |     |------------------------>|
       |    received from   |     |     INFO <dialog.exit>  |
       |    first dialog    |     |<------------------------|
       |                    |     |  200 OK                 |
       |                     \    |------------------------>|
       |  BYE                     |                         |
       |------------------------->|  BYE                    |
       |                          |------------------------>|
       |                      RTP stopped                   |
       |<< : : : : : : : : : : : : : : : : : : : : : : : :>>|
       |                          |                 200 OK  |
       |                          |<------------------------|
       |                  200 OK  |                         |
       |<-------------------------|                         |
       |                          |                         |

    The sample application server implements simple voice and video mail 
    functionality using MSML scripts and media recording files to perform all 
    media functions on the Media Server.  The Application Server uses HMP in 
    SIP 3PCC mode for call control.

2.0 System Requirements

    1. MSML Media Server
       PowerMedia XMS
    
    2. Application server
        Network file system access to media files on the Media Server
        HMP
            License requirements
                2 IP Call Control resources per channel
            Version requirements
                Linux
                    HMP 4.1
    
    3. SIP phone     
        Hardware or software based, see HMP documentation for supported devices

3.0 Installation and Configuration

Unzip the distribution file into a convenient directory.  This directory will 
be referred to as the <install> directory.

Install the application server executable and configuration on the Application 
Server by copying the app_server.exe and app_server.cfg files to a convenient 
directory.  The directory <install>\app_server\build\release contains the 
app_server executable and the directory <install>\app_server\data contains 
app_server.cfg.
        
The distribution script and media directories are located in the 
<install>\app_server\data directory.

Scrip and media files storage may be on a shared network drive or on an HTTP 
server.  If an HTTP server is used, it must support GET, PUT and DELETE 
commands.  The Microsoft Internet Information Server (IIS) can be configured 
to support PUT and DELETE by enabling write permission for the media 
directory.  The Apache HTTP Server supports PUT and DELETE by enabling the 
mod_dav module and configuring the container for the media directory.

The script files must be modified for the media file storage location as 
referenced to the MSML server.  Replace all instances of %MEDIA_URI_BASE%
in the script files with, for example, file://./msml/media for a local 
directory, or http://httphost/msml/media for use with an HTTP server.

An example of installing the MSML script and media support is to copy the media
and script directories to the PowerMedia XMS media directory. 

The directory structure on PowerMedia XMS is:

    /var/lib/xms/media/en-US/msml/
    
The resulting MSML media and script directories would be:

    /var/lib/xms/media/en-US/msml/media
    /var/lib/xms/media/en-US/msml/scripts

The application server configuration is contained in the text file 
app_server.cfg.  The following configuration items are available:

	1. Logging level by log object type

		log:<log object type>=<log level>

		where the log object types are:

			all
			system
			main
			eventmgr
			resource
			resourcemgr 
			resourcegrp
			resourcegrpmgr
			callflow
			callflowmgr

		and the log levels are:

			debug
			info
			warn
			error

		The default log level for all log object types is "info".

	2. The SIP port used by the application server

		port:<sip port> where the default SIP port is 5060

	3. URI of the Application Server

		app:<URI> where the URI is a SIP address. Example : 
		1234@192.168.1.61:5070

	4. URI of the MSML Media Server

		msml:<URI> where the URI is a SIP address. Example : 5678@192.168.1.51

	5. Maximum number of channels

		maxchan:<max channels> where max channels is the maximum number of SIP 
		resources to use.  Each session requires two SIP resources.  The default 
		maximum number of channels is 4.

	6. URI to the media file storage
	
        media:<URI> where the URI  for the a directory where media files are 
        stored.  file:// and http:// are supported.  file:// is relative
        to the Media Server.  
        
        The default media file storage URI is file:///media.
        
        Using the MSML media file location example above, the media file
        storage URI is file:///var/lib/xms/media/en-US/msml/media

	7. File path mapping to the media file storage
        
        The file path mapping is used by app_server for direct Mailbox media 
        file access when media file storage is filoe based with file://.
        
        mediafilemap:<path> where the path is the local application server path
        to the directory where media files are stored.  
        
        This value of path replaces file:// in media URIs when used.  
        
        The default file path mapping is /xms.
        
        Using the MSML media file location example above and assuming that
        /var/lib/xms/media/en-US/msml has been exported in NFS on the MSML 
        server and mounted on the app_server to /xms, the media file 
        storage path mapping is /xms       
        
        See the nfsreadme for notes on NFS setup.

	8. URI to the script file storage
    
        scripts:<URI> where the URI  is for the a directory where script files 
        are stored.  
        
        “file://” and “http://” are supported.  file:// is relative to the 
        Media Server.  
        
        The default script file storage URI is file:///scripts.

        Using the MSML media file storage example above, the script file
        storage URI is file:///var/lib/xms/media/en-US/msml/scripts

	9. Supported video confere3nce layouts
	
				The video layout
	
				layouts:1,2,4,6,9

	10. Initial video layout
	
				initiallayout:2

	11. Root size of video conference window

				rootsize: SQCIF, QCIF, CIF, QVGA, VGA, 720p, 720p_4x3
				
4.0 Operation

    The application server is started from a command prompt with the following 
    usage:

    Usage: app_server <options>
    options:
        [-h] [?] - display command line help
        [-maxchan:<max channels>] - maximum number of SIP channels, default: 4
        [-log:<objectType>=<log level> - set logging levels
              <objectType>= [system | main | eventmgr | resource | resourcemgr |
                             resourcegrp | resourcegrpmgr
                             callflow |callflowmgr]
              <log level> = [debug | info | warn | error>]
        [-port:<sip port>] - sip port, default:5060
        [-app:<URI>] - application server SIP address
               example: 1234@192.168.1.61:5070, default: 1@localhost
        [-msml:<URI>] - MSML Server SIP address
               example: 5678@192.168.1.51, default: 2@media_server
        [-media:<path>] - uri for media files from the Media Server(file:// or http://)
               default: file:///media
        [-mediafilemap:<path> - local path/dirve mapping to replace file:// if used
               default: /xms
        [-scripts:<uri>] - uri for script files(file:// or http://)
               default: file:///scripts
         [-rootsize:<size>] - size of the root video conference window
               <size> = 	[SQCIF | QCIF | CIF | QVGA | VGA | 720p | 720p_4x3]
               default: CIF
               
    Note that the command line parameters are also available as configuration 
    items in app_server.cfg.
    
    While app_server is running, commands may be entered in the console window. 
    Available commands are:
    
        Ctrl-C, 'q', "quit" - quit the application
        log:<objectType>=[debug|warn|info|error] - change the log level
        
    The menu structure presented to the caller is:
    
    Main Menu:
    
        1 - Voice Mail
        2 - Video Mail (available only on a video call)
        3 - Voice Conference (available only if supported by MSML Server)
        4 - Video Conference (available only if supported by MSML Server)
        * - Quit
        
        Voice and Video Mail have the same menu structure:
        
            1 - Record
                Enter 3 digit mailbox number between 101 and 299
                    2 - Start Record
                        2 - Stop Record
                            2 - Re-record
                            3 - Save
                            4 - Play
                            * - Quit
                        * - Quit
                    * - Quit
                * - Quit
            2 - Play
                Enter 3 digit mailbox number between 101 and 299
                    1 - Re-play
                    2 - Delete
                    * - Quit
                * - Quit
            * - Quit

        Conference menu structure:
        
            1 - Create Conference
                Enter 3 digit conference number between 101 and 299
                    * - Quit
            2 - Join Conference
                Enter 3 digit conference number between 101 and 299
                    * - Quit
                * - Quit
            * - Quit

5.0 Building the application

    Linux build requirements:
    
        HMP 4.1 for Linux
        Boost Libraries 1.33.1
        cURL Library 7.16.2
    
    The source distribution includes a makefile for Linux.  These files are 
    located in the <install>\build directory.  They are intended to be run 
    from that directory.
    
    The Boost and cURL libraries are noramlly automatically installed on Linux.    
    
    For reference, the following Boost libraries are used:
    
        Bind - Generalization of the std::bindNxx functions
        Format - Format arguments using a format-string to an internal stream
        Function - Function object wrappers
        Smart Pointers - Automatic ownership and lifetime management
        Threads - Portable threading and synchronization
        Utility - Misc features including a noncopyable base class
      
    To build the application on Linux, change the current directory to 
    <install>\build, and run either 'make debug' or 'make release'.  The command 
    'make clean' will remove all intermediate and executable files for both 
    debug and release.

6.0 Distribution Contents

    The distribution contains the following directories and files:
        app_server\
        app_server\build\
        app_server\build\makefile
        app_server\build\debug\
        app_server\build\release\
        app_server\build\release\app_server (Linux executable)
        app_server\data\
        app_server\data\app_server.cfg
        app_server\data\media\
        app_server\data\media\*.pcm, *.vid, *.wav
        app_server\data\scripts\
        app_server\data\scripts\*.moml
        app_server\docs\
        app_server\docs\readme.txt (this file)
        app_server\docs\nfsreadme.txt
        app_server\src\
        app_server\src\*.cpp, *.h
