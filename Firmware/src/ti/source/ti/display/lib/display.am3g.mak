#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = gnu.targets.arm.M3{1,0,4.9,3
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/display/package/package_ti.display.om3g.dep
package/lib/lib/display/package/package_ti.display.om3g.dep: ;
endif

package/lib/lib/display/package/package_ti.display.om3g: | .interfaces
package/lib/lib/display/package/package_ti.display.om3g: package/package_ti.display.c lib/display.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_3  -O2   -I.  -I/db/vtree/library/trees/mcpi/mcpi-b14/exports/coresdk_cc13xx_cc26xx_3_01_00_14/kernel/tirtos/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/display/package/package_ti.display.om3g: export LD_LIBRARY_PATH=

package/lib/lib/display/package/package_ti.display.sm3g: | .interfaces
package/lib/lib/display/package/package_ti.display.sm3g: package/package_ti.display.c lib/display.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g -S $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_3  -O2   -I.   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/display/package/package_ti.display.sm3g: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/display/Display.om3g.dep
package/lib/lib/display/Display.om3g.dep: ;
endif

package/lib/lib/display/Display.om3g: | .interfaces
package/lib/lib/display/Display.om3g: Display.c lib/display.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_3  -O2   -I.  -I/db/vtree/library/trees/mcpi/mcpi-b14/exports/coresdk_cc13xx_cc26xx_3_01_00_14/kernel/tirtos/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/display/Display.om3g: export LD_LIBRARY_PATH=

package/lib/lib/display/Display.sm3g: | .interfaces
package/lib/lib/display/Display.sm3g: Display.c lib/display.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g -S $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_3  -O2   -I.   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/display/Display.sm3g: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/display/DisplayHost.om3g.dep
package/lib/lib/display/DisplayHost.om3g.dep: ;
endif

package/lib/lib/display/DisplayHost.om3g: | .interfaces
package/lib/lib/display/DisplayHost.om3g: DisplayHost.c lib/display.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_3  -O2   -I.  -I/db/vtree/library/trees/mcpi/mcpi-b14/exports/coresdk_cc13xx_cc26xx_3_01_00_14/kernel/tirtos/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/display/DisplayHost.om3g: export LD_LIBRARY_PATH=

package/lib/lib/display/DisplayHost.sm3g: | .interfaces
package/lib/lib/display/DisplayHost.sm3g: DisplayHost.c lib/display.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g -S $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_3  -O2   -I.   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/display/DisplayHost.sm3g: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/display/DisplayUart.om3g.dep
package/lib/lib/display/DisplayUart.om3g.dep: ;
endif

package/lib/lib/display/DisplayUart.om3g: | .interfaces
package/lib/lib/display/DisplayUart.om3g: DisplayUart.c lib/display.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_3  -O2   -I.  -I/db/vtree/library/trees/mcpi/mcpi-b14/exports/coresdk_cc13xx_cc26xx_3_01_00_14/kernel/tirtos/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/display/DisplayUart.om3g: export LD_LIBRARY_PATH=

package/lib/lib/display/DisplayUart.sm3g: | .interfaces
package/lib/lib/display/DisplayUart.sm3g: DisplayUart.c lib/display.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g -S $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_3  -O2   -I.   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/display/DisplayUart.sm3g: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/display/DisplaySharp.om3g.dep
package/lib/lib/display/DisplaySharp.om3g.dep: ;
endif

package/lib/lib/display/DisplaySharp.om3g: | .interfaces
package/lib/lib/display/DisplaySharp.om3g: DisplaySharp.c lib/display.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_3  -O2   -I.  -I/db/vtree/library/trees/mcpi/mcpi-b14/exports/coresdk_cc13xx_cc26xx_3_01_00_14/kernel/tirtos/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/display/DisplaySharp.om3g: export LD_LIBRARY_PATH=

package/lib/lib/display/DisplaySharp.sm3g: | .interfaces
package/lib/lib/display/DisplaySharp.sm3g: DisplaySharp.c lib/display.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g -S $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_3  -O2   -I.   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/display/DisplaySharp.sm3g: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/display/DisplayExt.om3g.dep
package/lib/lib/display/DisplayExt.om3g.dep: ;
endif

package/lib/lib/display/DisplayExt.om3g: | .interfaces
package/lib/lib/display/DisplayExt.om3g: DisplayExt.c lib/display.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_3  -O2   -I.  -I/db/vtree/library/trees/mcpi/mcpi-b14/exports/coresdk_cc13xx_cc26xx_3_01_00_14/kernel/tirtos/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/display/DisplayExt.om3g: export LD_LIBRARY_PATH=

package/lib/lib/display/DisplayExt.sm3g: | .interfaces
package/lib/lib/display/DisplayExt.sm3g: DisplayExt.c lib/display.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g -S $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_3  -O2   -I.   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/display/DisplayExt.sm3g: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/display/DisplayDogm1286.om3g.dep
package/lib/lib/display/DisplayDogm1286.om3g.dep: ;
endif

package/lib/lib/display/DisplayDogm1286.om3g: | .interfaces
package/lib/lib/display/DisplayDogm1286.om3g: DisplayDogm1286.c lib/display.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_3  -O2   -I.  -I/db/vtree/library/trees/mcpi/mcpi-b14/exports/coresdk_cc13xx_cc26xx_3_01_00_14/kernel/tirtos/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/display/DisplayDogm1286.om3g: export LD_LIBRARY_PATH=

package/lib/lib/display/DisplayDogm1286.sm3g: | .interfaces
package/lib/lib/display/DisplayDogm1286.sm3g: DisplayDogm1286.c lib/display.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g -S $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_3  -O2   -I.   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/display/DisplayDogm1286.sm3g: export LD_LIBRARY_PATH=

clean,m3g ::
	-$(RM) package/lib/lib/display/package/package_ti.display.om3g
	-$(RM) package/lib/lib/display/Display.om3g
	-$(RM) package/lib/lib/display/DisplayHost.om3g
	-$(RM) package/lib/lib/display/DisplayUart.om3g
	-$(RM) package/lib/lib/display/DisplaySharp.om3g
	-$(RM) package/lib/lib/display/DisplayExt.om3g
	-$(RM) package/lib/lib/display/DisplayDogm1286.om3g
	-$(RM) package/lib/lib/display/package/package_ti.display.sm3g
	-$(RM) package/lib/lib/display/Display.sm3g
	-$(RM) package/lib/lib/display/DisplayHost.sm3g
	-$(RM) package/lib/lib/display/DisplayUart.sm3g
	-$(RM) package/lib/lib/display/DisplaySharp.sm3g
	-$(RM) package/lib/lib/display/DisplayExt.sm3g
	-$(RM) package/lib/lib/display/DisplayDogm1286.sm3g

lib/display.am3g: package/lib/lib/display/package/package_ti.display.om3g package/lib/lib/display/Display.om3g package/lib/lib/display/DisplayHost.om3g package/lib/lib/display/DisplayUart.om3g package/lib/lib/display/DisplaySharp.om3g package/lib/lib/display/DisplayExt.om3g package/lib/lib/display/DisplayDogm1286.om3g lib/display.am3g.mak

clean::
	-$(RM) lib/display.am3g.mak
