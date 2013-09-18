# ============================================================================
#  Name	 : build_help.mk
#  Part of  : Symbian3
#
#  Description: This make file will build the application help file (.hlp)
# 
# ============================================================================

do_nothing :
	@rem do_nothing

MAKMAKE :
	cshlpcmp BlackList_01.cshlp
	cshlpcmp BlackList_04.cshlp
	cshlpcmp BlackList_16.cshlp
	cshlpcmp BlackList_03.cshlp
ifeq (WINS,$(findstring WINS, $(PLATFORM)))
	copy AAction_2003A2C8.h01 $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
	copy AAction_2003A2C8.h03 $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
	copy AAction_2003A2C8.h04 $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
	copy AAction_2003A2C8.h16 $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
endif

BLD : do_nothing

CLEAN :
	del AAction_2003A2C8.h01
	del AAction_2003A2C8.h01.hrh
	del AAction_2003A2C8.h03
	del AAction_2003A2C8.h03.hrh
	del AAction_2003A2C8.h04
	del AAction_2003A2C8.h04.hrh	
	del AAction_2003A2C8.h16
	del AAction_2003A2C8.h16.hrh

LIB : do_nothing

CLEANLIB : do_nothing

RESOURCE : do_nothing
		
FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES :
	@echo AAction_2003A2C8.h03
	@echo AAction_2003A2C8.h04
	@echo AAction_2003A2C8.h16
	@echo AAction_2003A2C8.h01

FINAL : do_nothing
