ifeq (WINS,$(findstring WINS, $(PLATFORM)))
ZDIR=$(EPOCROOT)epoc32\release\$(PLATFORM)\$(CFG)\Z
else
ZDIR=$(EPOCROOT)epoc32\data\z
endif

TARGETDIR=$(ZDIR)\resource\apps
HEADERDIR=$(EPOCROOT)\epoc32\include

do_nothing :
	@rem do_nothing

MAKMAKE : do_nothing

BLD : do_nothing

CLEAN : do_nothing

LIB : do_nothing

CLEANLIB : do_nothing

RESOURCE : $(TARGETDIR)\AAction_aif.mif $(TARGETDIR)\AAction.mif

$(TARGETDIR)\AAction_aif.mif: ..\data\PromoteExample_reg.miflist
#	mifconv $(TARGETDIR)\AAction_aif.mif /h$(HEADERDIR)\AAction_aif.mbg /X /F..\data\PromoteExample_reg.miflist
	mifconv $(TARGETDIR)\AAction_aif.mif /h$(HEADERDIR)\AAction_aif.mbg /F..\data\PromoteExample_reg.miflist
$(TARGETDIR)\AAction.mif: ..\data\PromoteExample.miflist
#	mifconv $(TARGETDIR)\AAction.mif /h$(HEADERDIR)\AAction.mbg /X /F..\data\PromoteExample.miflist 
	mifconv $(TARGETDIR)\AAction.mif /h$(HEADERDIR)\AAction.mbg /F..\data\PromoteExample.miflist


FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES :
	@echo $(TARGETDIR)\AAction_aif.mif&& \
	@echo (HEADERDIR)\AAction_aif.mbg
	@echo $(TARGETDIR)\AAction.mif&& \
	@echo (HEADERDIR)\AAction.mbg

FINAL : do_nothing
