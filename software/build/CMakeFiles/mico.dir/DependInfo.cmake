
# Consider dependencies only in project.
set(CMAKE_DEPENDS_IN_PROJECT_ONLY OFF)

# The set of languages for which implicit dependencies are needed:
set(CMAKE_DEPENDS_LANGUAGES
  "ASM"
  )
# The set of files for implicit dependencies of each language:
set(CMAKE_DEPENDS_CHECK_ASM
  "/usr/share/pico-sdk/src/rp2_common/hardware_divider/divider.S" "/home/mads/code/mcu/mico/software/build/CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_divider/divider.S.obj"
  "/usr/share/pico-sdk/src/rp2_common/hardware_irq/irq_handler_chain.S" "/home/mads/code/mcu/mico/software/build/CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_irq/irq_handler_chain.S.obj"
  "/usr/share/pico-sdk/src/rp2_common/pico_bit_ops/bit_ops_aeabi.S" "/home/mads/code/mcu/mico/software/build/CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_bit_ops/bit_ops_aeabi.S.obj"
  "/usr/share/pico-sdk/src/rp2_common/pico_divider/divider.S" "/home/mads/code/mcu/mico/software/build/CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_divider/divider.S.obj"
  "/usr/share/pico-sdk/src/rp2_common/pico_double/double_aeabi.S" "/home/mads/code/mcu/mico/software/build/CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_double/double_aeabi.S.obj"
  "/usr/share/pico-sdk/src/rp2_common/pico_double/double_v1_rom_shim.S" "/home/mads/code/mcu/mico/software/build/CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_double/double_v1_rom_shim.S.obj"
  "/usr/share/pico-sdk/src/rp2_common/pico_float/float_aeabi.S" "/home/mads/code/mcu/mico/software/build/CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_float/float_aeabi.S.obj"
  "/usr/share/pico-sdk/src/rp2_common/pico_float/float_v1_rom_shim.S" "/home/mads/code/mcu/mico/software/build/CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_float/float_v1_rom_shim.S.obj"
  "/usr/share/pico-sdk/src/rp2_common/pico_int64_ops/pico_int64_ops_aeabi.S" "/home/mads/code/mcu/mico/software/build/CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_int64_ops/pico_int64_ops_aeabi.S.obj"
  "/usr/share/pico-sdk/src/rp2_common/pico_mem_ops/mem_ops_aeabi.S" "/home/mads/code/mcu/mico/software/build/CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_mem_ops/mem_ops_aeabi.S.obj"
  "/usr/share/pico-sdk/src/rp2_common/pico_standard_link/crt0.S" "/home/mads/code/mcu/mico/software/build/CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_standard_link/crt0.S.obj"
  )
set(CMAKE_ASM_COMPILER_ID "GNU")

# Preprocessor definitions for this target.
set(CMAKE_TARGET_DEFINITIONS_ASM
  "CFG_TUSB_DEBUG=0"
  "CFG_TUSB_MCU=OPT_MCU_RP2040"
  "CFG_TUSB_OS=OPT_OS_PICO"
  "LIB_PICO_BIT_OPS=1"
  "LIB_PICO_BIT_OPS_PICO=1"
  "LIB_PICO_DIVIDER=1"
  "LIB_PICO_DIVIDER_HARDWARE=1"
  "LIB_PICO_DOUBLE=1"
  "LIB_PICO_DOUBLE_PICO=1"
  "LIB_PICO_FIX_RP2040_USB_DEVICE_ENUMERATION=1"
  "LIB_PICO_FLOAT=1"
  "LIB_PICO_FLOAT_PICO=1"
  "LIB_PICO_INT64_OPS=1"
  "LIB_PICO_INT64_OPS_PICO=1"
  "LIB_PICO_MALLOC=1"
  "LIB_PICO_MEM_OPS=1"
  "LIB_PICO_MEM_OPS_PICO=1"
  "LIB_PICO_MULTICORE=1"
  "LIB_PICO_PLATFORM=1"
  "LIB_PICO_PRINTF=1"
  "LIB_PICO_PRINTF_PICO=1"
  "LIB_PICO_RUNTIME=1"
  "LIB_PICO_STANDARD_LINK=1"
  "LIB_PICO_STDIO=1"
  "LIB_PICO_STDIO_USB=1"
  "LIB_PICO_STDLIB=1"
  "LIB_PICO_SYNC=1"
  "LIB_PICO_SYNC_CORE=1"
  "LIB_PICO_SYNC_CRITICAL_SECTION=1"
  "LIB_PICO_SYNC_MUTEX=1"
  "LIB_PICO_SYNC_SEM=1"
  "LIB_PICO_TIME=1"
  "LIB_PICO_UNIQUE_ID=1"
  "LIB_PICO_UTIL=1"
  "PICO_BOARD=\"pico\""
  "PICO_BUILD=1"
  "PICO_CMAKE_BUILD_TYPE=\"Release\""
  "PICO_COPY_TO_RAM=0"
  "PICO_CXX_ENABLE_EXCEPTIONS=0"
  "PICO_NO_FLASH=0"
  "PICO_NO_HARDWARE=0"
  "PICO_ON_DEVICE=1"
  "PICO_PROGRAM_NAME=\"mico\""
  "PICO_PROGRAM_VERSION_STRING=\"0.1\""
  "PICO_TARGET_NAME=\"mico\""
  "PICO_USE_BLOCKED_RAM=0"
  )

# The include file search paths:
set(CMAKE_ASM_TARGET_INCLUDE_PATH
  "."
  "/usr/share/pico-sdk/src/common/pico_stdlib/include"
  "/usr/share/pico-sdk/src/rp2_common/hardware_gpio/include"
  "/usr/share/pico-sdk/src/common/pico_base/include"
  "generated/pico_base"
  "/usr/share/pico-sdk/src/boards/include"
  "/usr/share/pico-sdk/src/rp2_common/pico_platform/include"
  "/usr/share/pico-sdk/src/rp2040/hardware_regs/include"
  "/usr/share/pico-sdk/src/rp2_common/hardware_base/include"
  "/usr/share/pico-sdk/src/rp2040/hardware_structs/include"
  "/usr/share/pico-sdk/src/rp2_common/hardware_claim/include"
  "/usr/share/pico-sdk/src/rp2_common/hardware_sync/include"
  "/usr/share/pico-sdk/src/rp2_common/hardware_uart/include"
  "/usr/share/pico-sdk/src/rp2_common/hardware_divider/include"
  "/usr/share/pico-sdk/src/common/pico_time/include"
  "/usr/share/pico-sdk/src/rp2_common/hardware_timer/include"
  "/usr/share/pico-sdk/src/common/pico_sync/include"
  "/usr/share/pico-sdk/src/common/pico_util/include"
  "/usr/share/pico-sdk/src/rp2_common/pico_runtime/include"
  "/usr/share/pico-sdk/src/rp2_common/hardware_clocks/include"
  "/usr/share/pico-sdk/src/rp2_common/hardware_irq/include"
  "/usr/share/pico-sdk/src/rp2_common/hardware_resets/include"
  "/usr/share/pico-sdk/src/rp2_common/hardware_pll/include"
  "/usr/share/pico-sdk/src/rp2_common/hardware_vreg/include"
  "/usr/share/pico-sdk/src/rp2_common/hardware_watchdog/include"
  "/usr/share/pico-sdk/src/rp2_common/hardware_xosc/include"
  "/usr/share/pico-sdk/src/rp2_common/pico_printf/include"
  "/usr/share/pico-sdk/src/rp2_common/pico_bootrom/include"
  "/usr/share/pico-sdk/src/common/pico_bit_ops/include"
  "/usr/share/pico-sdk/src/common/pico_divider/include"
  "/usr/share/pico-sdk/src/rp2_common/pico_double/include"
  "/usr/share/pico-sdk/src/rp2_common/pico_int64_ops/include"
  "/usr/share/pico-sdk/src/rp2_common/pico_float/include"
  "/usr/share/pico-sdk/src/rp2_common/pico_malloc/include"
  "/usr/share/pico-sdk/src/rp2_common/boot_stage2/include"
  "/usr/share/pico-sdk/src/common/pico_binary_info/include"
  "/usr/share/pico-sdk/src/rp2_common/pico_stdio/include"
  "/usr/share/pico-sdk/src/rp2_common/pico_stdio_usb/include"
  "/usr/share/pico-sdk/lib/tinyusb/src"
  "/usr/share/pico-sdk/lib/tinyusb/src/common"
  "/usr/share/pico-sdk/lib/tinyusb/hw"
  "/usr/share/pico-sdk/src/rp2_common/pico_fix/rp2040_usb_device_enumeration/include"
  "/usr/share/pico-sdk/src/rp2_common/pico_unique_id/include"
  "/usr/share/pico-sdk/src/rp2_common/hardware_flash/include"
  "/usr/share/pico-sdk/src/common/pico_usb_reset_interface/include"
  "libs/encoder-pio"
  "../libs/encoder-pio"
  "/usr/share/pico-sdk/src/rp2_common/hardware_pio/include"
  "/usr/share/pico-sdk/src/rp2_common/pico_multicore/include"
  "/usr/share/pico-sdk/src/rp2_common/hardware_interp/include"
  )

# The set of dependency files which are needed:
set(CMAKE_DEPENDS_DEPENDENCY_FILES
  "/usr/share/pico-sdk/lib/tinyusb/src/class/audio/audio_device.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/audio/audio_device.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/audio/audio_device.c.obj.d"
  "/usr/share/pico-sdk/lib/tinyusb/src/class/cdc/cdc_device.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/cdc/cdc_device.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/cdc/cdc_device.c.obj.d"
  "/usr/share/pico-sdk/lib/tinyusb/src/class/dfu/dfu_device.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/dfu/dfu_device.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/dfu/dfu_device.c.obj.d"
  "/usr/share/pico-sdk/lib/tinyusb/src/class/dfu/dfu_rt_device.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/dfu/dfu_rt_device.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/dfu/dfu_rt_device.c.obj.d"
  "/usr/share/pico-sdk/lib/tinyusb/src/class/hid/hid_device.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/hid/hid_device.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/hid/hid_device.c.obj.d"
  "/usr/share/pico-sdk/lib/tinyusb/src/class/midi/midi_device.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/midi/midi_device.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/midi/midi_device.c.obj.d"
  "/usr/share/pico-sdk/lib/tinyusb/src/class/msc/msc_device.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/msc/msc_device.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/msc/msc_device.c.obj.d"
  "/usr/share/pico-sdk/lib/tinyusb/src/class/net/ecm_rndis_device.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/net/ecm_rndis_device.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/net/ecm_rndis_device.c.obj.d"
  "/usr/share/pico-sdk/lib/tinyusb/src/class/net/ncm_device.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/net/ncm_device.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/net/ncm_device.c.obj.d"
  "/usr/share/pico-sdk/lib/tinyusb/src/class/usbtmc/usbtmc_device.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/usbtmc/usbtmc_device.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/usbtmc/usbtmc_device.c.obj.d"
  "/usr/share/pico-sdk/lib/tinyusb/src/class/vendor/vendor_device.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/vendor/vendor_device.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/vendor/vendor_device.c.obj.d"
  "/usr/share/pico-sdk/lib/tinyusb/src/class/video/video_device.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/video/video_device.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/class/video/video_device.c.obj.d"
  "/usr/share/pico-sdk/lib/tinyusb/src/common/tusb_fifo.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/common/tusb_fifo.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/common/tusb_fifo.c.obj.d"
  "/usr/share/pico-sdk/lib/tinyusb/src/device/usbd.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/device/usbd.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/device/usbd.c.obj.d"
  "/usr/share/pico-sdk/lib/tinyusb/src/device/usbd_control.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/device/usbd_control.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/device/usbd_control.c.obj.d"
  "/usr/share/pico-sdk/lib/tinyusb/src/portable/raspberrypi/rp2040/dcd_rp2040.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/portable/raspberrypi/rp2040/dcd_rp2040.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/portable/raspberrypi/rp2040/dcd_rp2040.c.obj.d"
  "/usr/share/pico-sdk/lib/tinyusb/src/portable/raspberrypi/rp2040/rp2040_usb.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/portable/raspberrypi/rp2040/rp2040_usb.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/portable/raspberrypi/rp2040/rp2040_usb.c.obj.d"
  "/usr/share/pico-sdk/lib/tinyusb/src/tusb.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/tusb.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/lib/tinyusb/src/tusb.c.obj.d"
  "/usr/share/pico-sdk/src/common/pico_sync/critical_section.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/common/pico_sync/critical_section.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/common/pico_sync/critical_section.c.obj.d"
  "/usr/share/pico-sdk/src/common/pico_sync/lock_core.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/common/pico_sync/lock_core.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/common/pico_sync/lock_core.c.obj.d"
  "/usr/share/pico-sdk/src/common/pico_sync/mutex.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/common/pico_sync/mutex.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/common/pico_sync/mutex.c.obj.d"
  "/usr/share/pico-sdk/src/common/pico_sync/sem.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/common/pico_sync/sem.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/common/pico_sync/sem.c.obj.d"
  "/usr/share/pico-sdk/src/common/pico_time/time.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/common/pico_time/time.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/common/pico_time/time.c.obj.d"
  "/usr/share/pico-sdk/src/common/pico_time/timeout_helper.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/common/pico_time/timeout_helper.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/common/pico_time/timeout_helper.c.obj.d"
  "/usr/share/pico-sdk/src/common/pico_util/datetime.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/common/pico_util/datetime.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/common/pico_util/datetime.c.obj.d"
  "/usr/share/pico-sdk/src/common/pico_util/pheap.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/common/pico_util/pheap.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/common/pico_util/pheap.c.obj.d"
  "/usr/share/pico-sdk/src/common/pico_util/queue.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/common/pico_util/queue.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/common/pico_util/queue.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/hardware_claim/claim.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_claim/claim.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_claim/claim.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/hardware_clocks/clocks.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_clocks/clocks.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_clocks/clocks.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/hardware_flash/flash.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_flash/flash.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_flash/flash.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/hardware_gpio/gpio.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_gpio/gpio.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_gpio/gpio.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/hardware_interp/interp.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_interp/interp.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_interp/interp.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/hardware_irq/irq.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_irq/irq.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_irq/irq.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/hardware_pio/pio.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_pio/pio.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_pio/pio.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/hardware_pll/pll.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_pll/pll.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_pll/pll.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/hardware_sync/sync.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_sync/sync.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_sync/sync.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/hardware_timer/timer.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_timer/timer.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_timer/timer.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/hardware_uart/uart.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_uart/uart.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_uart/uart.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/hardware_vreg/vreg.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_vreg/vreg.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_vreg/vreg.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/hardware_watchdog/watchdog.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_watchdog/watchdog.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_watchdog/watchdog.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/hardware_xosc/xosc.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_xosc/xosc.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/hardware_xosc/xosc.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/pico_bootrom/bootrom.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_bootrom/bootrom.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_bootrom/bootrom.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/pico_double/double_init_rom.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_double/double_init_rom.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_double/double_init_rom.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/pico_double/double_math.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_double/double_math.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_double/double_math.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/pico_fix/rp2040_usb_device_enumeration/rp2040_usb_device_enumeration.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_fix/rp2040_usb_device_enumeration/rp2040_usb_device_enumeration.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_fix/rp2040_usb_device_enumeration/rp2040_usb_device_enumeration.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/pico_float/float_init_rom.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_float/float_init_rom.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_float/float_init_rom.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/pico_float/float_math.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_float/float_math.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_float/float_math.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/pico_malloc/pico_malloc.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_malloc/pico_malloc.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_malloc/pico_malloc.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/pico_multicore/multicore.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_multicore/multicore.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_multicore/multicore.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/pico_platform/platform.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_platform/platform.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_platform/platform.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/pico_printf/printf.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_printf/printf.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_printf/printf.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/pico_runtime/runtime.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_runtime/runtime.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_runtime/runtime.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/pico_standard_link/binary_info.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_standard_link/binary_info.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_standard_link/binary_info.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/pico_stdio/stdio.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_stdio/stdio.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_stdio/stdio.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/pico_stdio_usb/reset_interface.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_stdio_usb/reset_interface.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_stdio_usb/reset_interface.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/pico_stdio_usb/stdio_usb.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_stdio_usb/stdio_usb.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_stdio_usb/stdio_usb.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/pico_stdio_usb/stdio_usb_descriptors.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_stdio_usb/stdio_usb_descriptors.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_stdio_usb/stdio_usb_descriptors.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/pico_stdlib/stdlib.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_stdlib/stdlib.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_stdlib/stdlib.c.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/pico_unique_id/unique_id.c" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_unique_id/unique_id.c.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_unique_id/unique_id.c.obj.d"
  "/home/mads/code/mcu/mico/software/libs/encoder-pio/capture.cpp" "CMakeFiles/mico.dir/libs/encoder-pio/capture.cpp.obj" "gcc" "CMakeFiles/mico.dir/libs/encoder-pio/capture.cpp.obj.d"
  "/home/mads/code/mcu/mico/software/libs/encoder-pio/encoder.cpp" "CMakeFiles/mico.dir/libs/encoder-pio/encoder.cpp.obj" "gcc" "CMakeFiles/mico.dir/libs/encoder-pio/encoder.cpp.obj.d"
  "/home/mads/code/mcu/mico/software/mico.cpp" "CMakeFiles/mico.dir/mico.cpp.obj" "gcc" "CMakeFiles/mico.dir/mico.cpp.obj.d"
  "/usr/share/pico-sdk/src/rp2_common/pico_standard_link/new_delete.cpp" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_standard_link/new_delete.cpp.obj" "gcc" "CMakeFiles/mico.dir/usr/share/pico-sdk/src/rp2_common/pico_standard_link/new_delete.cpp.obj.d"
  )

# Targets to which this target links.
set(CMAKE_TARGET_LINKED_INFO_FILES
  )

# Fortran module output directory.
set(CMAKE_Fortran_TARGET_MODULE_DIR "")
