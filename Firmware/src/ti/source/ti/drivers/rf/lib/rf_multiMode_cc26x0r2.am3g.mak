#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = gnu.targets.arm.M3{1,0,4.9,3
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/rf_multiMode_cc26x0r2/package/package_ti.drivers.rf.om3g.dep
package/lib/lib/rf_multiMode_cc26x0r2/package/package_ti.drivers.rf.om3g.dep: ;
endif

package/lib/lib/rf_multiMode_cc26x0r2/package/package_ti.drivers.rf.om3g: | .interfaces
package/lib/lib/rf_multiMode_cc26x0r2/package/package_ti.drivers.rf.om3g: package/package_ti.drivers.rf.c lib/rf_multiMode_cc26x0r2.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_3  -O2   -DDEVICE_FAMILY=cc26x0r2 -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL -I/db/vtree/library/trees/mcpi/mcpi-b14/exports/coresdk_cc13xx_cc26xx_3_01_00_14/kernel/tirtos/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/rf_multiMode_cc26x0r2/package/package_ti.drivers.rf.om3g: export LD_LIBRARY_PATH=

package/lib/lib/rf_multiMode_cc26x0r2/package/package_ti.drivers.rf.sm3g: | .interfaces
package/lib/lib/rf_multiMode_cc26x0r2/package/package_ti.drivers.rf.sm3g: package/package_ti.drivers.rf.c lib/rf_multiMode_cc26x0r2.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g -S $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_3  -O2   -DDEVICE_FAMILY=cc26x0r2 -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/rf_multiMode_cc26x0r2/package/package_ti.drivers.rf.sm3g: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/rf_multiMode_cc26x0r2/./RFCC26XX_multiMode.om3g.dep
package/lib/lib/rf_multiMode_cc26x0r2/./RFCC26XX_multiMode.om3g.dep: ;
endif

package/lib/lib/rf_multiMode_cc26x0r2/./RFCC26XX_multiMode.om3g: | .interfaces
package/lib/lib/rf_multiMode_cc26x0r2/./RFCC26XX_multiMode.om3g: ./RFCC26XX_multiMode.c lib/rf_multiMode_cc26x0r2.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_3  -O2   -DDEVICE_FAMILY=cc26x0r2 -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL -I/db/vtree/library/trees/mcpi/mcpi-b14/exports/coresdk_cc13xx_cc26xx_3_01_00_14/kernel/tirtos/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/rf_multiMode_cc26x0r2/./RFCC26XX_multiMode.om3g: export LD_LIBRARY_PATH=

package/lib/lib/rf_multiMode_cc26x0r2/./RFCC26XX_multiMode.sm3g: | .interfaces
package/lib/lib/rf_multiMode_cc26x0r2/./RFCC26XX_multiMode.sm3g: ./RFCC26XX_multiMode.c lib/rf_multiMode_cc26x0r2.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g -S $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_9_3  -O2   -DDEVICE_FAMILY=cc26x0r2 -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/rf_multiMode_cc26x0r2/./RFCC26XX_multiMode.sm3g: export LD_LIBRARY_PATH=

clean,m3g ::
	-$(RM) package/lib/lib/rf_multiMode_cc26x0r2/package/package_ti.drivers.rf.om3g
	-$(RM) package/lib/lib/rf_multiMode_cc26x0r2/./RFCC26XX_multiMode.om3g
	-$(RM) package/lib/lib/rf_multiMode_cc26x0r2/package/package_ti.drivers.rf.sm3g
	-$(RM) package/lib/lib/rf_multiMode_cc26x0r2/./RFCC26XX_multiMode.sm3g

lib/rf_multiMode_cc26x0r2.am3g: package/lib/lib/rf_multiMode_cc26x0r2/package/package_ti.drivers.rf.om3g package/lib/lib/rf_multiMode_cc26x0r2/./RFCC26XX_multiMode.om3g lib/rf_multiMode_cc26x0r2.am3g.mak

clean::
	-$(RM) lib/rf_multiMode_cc26x0r2.am3g.mak