# Title:
Python + FUSE

# Audience Level:
Intermediate

# Brief Outline: (1 Paragraph, 400 chars max)
FUSE allows you to fake a filesystem in your userspace without mucking
around in the kernel. This allows you to do things like showing remote
cloud-based backup products as local filesystems. This talk explores
such an implementation for mounting a Copy.com account as a local
filesystem, and addresses some of the common gotchas to help you
implement a FUSE layer for your preferred service.

# Detailed Abstract (Detailed description and outline)

## What is FUSE?

* Filesystem in Userspace
* an abstraction layer between non-priveleged user code and the
  kernel/kernel modules
* has been in the Linux kernel since 2.6.14
* https://en.wikipedia.org/wiki/File:FUSE_structure.svg
* available on Linux, FreeBSD, NetBSD, Android, Mac OS X, and more.
* Can run on the Raspberry Pi (more on that later)
	
The end result of this is that you can can create a
translation/abstraction layer between some data and your 'real'
filesystem - AKA "fake a filesystem"

## Why use FUSE?

* You can fake cloud storage accounts as local drives!!!
	
Lets ponder that for a second; that fact is awesome! Say that you have
a Copy.com, Box.net, Dropbox account, whatever, and you don't want to
(or can't) run their sync agents/applications. FUSE is your saviour
in this case. You can use the 3rd party API's that these services have
and make a FUSE layer between their API and your filesystem

## Copy.com and FUSE

* I am a developer on Copy, but I cannot run the GNU/Linux sync
  agent/desktop app.
* I can however run FUSE
* Maybe some quick highlights of Copy

### Enter copy-fuse

* I encourage you to fork the copy-fuse repo at
      https://github.com/copy-app/copy-fuse.git

Remember how I said that you can run a python FUSE layer on the
Raspberry Pi, well this fact is important because you can mount your
cloud storage as a local filesystem on hardware that isn't supported
by the cloud storage provider's sync agent/desktop app. This means
that you can use your Copy.com account _in real time_ on non-supported
hardware!!!

## Cue Raspberry Pi + copy-fuse demo
* Edit a document
* watch a movie/play a song

## Technical Details of a FUSE layer

* You have to determine what each 'real' filesystem operation means to
  your cloud storage provider (Some example operations):
    * chmod
	* chown
	* statfs
	* getattr
	* mkdir
	* open
	* flush
	* fsync
	* release
	* read
	* create
	* truncate
	* unlink/link
	* rmdir
	* write
	
* You don't have to implement a full filesystem
    * The FS operations that you don't want to support in your FUSE
      layer, you must NULL-OP.
	* The FS operations that mean something different to your data
      stream need to be implemented

## Implementing your own FUSE layer

* Remember how at the beginning I mentioned that you can use the cloud
  storage provider's API? And did you see any OAUTH or API stuff in
  the copy-fuse example?
    * The point here is that you can get around API's if you are
      willing to do trial and error.
* The possible data sources to map fake a FS with using FUSE are
  endless
    * show your tweets as files in a folder corresponding to the date
      that they were tweeted
	* show contacts as files
	* you get the idea

## Closing Remarks

* FUSE is pretty cool
* Python is pretty cool
* Python + FUSE is [mind blown gif]
* Python due to its ability to be run on many many platforms, plus
  FUSE gives you ton of "faked" local storage
