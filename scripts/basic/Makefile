###
<<<<<<< HEAD
# Makefile.basic lists the most basic programs used during the build process.
# The programs listed herein are what are needed to do the basic stuff,
# such as fix file dependencies.
=======
# Makefile.basic list the most basic programs used during the build process.
# The programs listed herein is what is needed to do the basic stuff,
# such as fix dependency file.
>>>>>>> 2e3646e51b2d... kconfig: integrate split config into silentoldconfig
# This initial step is needed to avoid files to be recompiled
# when kernel configuration changes (which is what happens when
# .config is included by main Makefile.
# ---------------------------------------------------------------------------
# fixdep: 	 Used to generate dependency information during build process
<<<<<<< HEAD

hostprogs-y	:= fixdep
hostprogs-$(CONFIG_BUILD_BIN2C)     += bin2c
=======
# docproc:	 Used in Documentation/docbook

hostprogs-y	:= fixdep docproc
>>>>>>> 2e3646e51b2d... kconfig: integrate split config into silentoldconfig
always		:= $(hostprogs-y)

# fixdep is needed to compile other host programs
$(addprefix $(obj)/,$(filter-out fixdep,$(always))): $(obj)/fixdep
