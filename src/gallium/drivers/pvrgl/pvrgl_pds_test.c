/* pvrgl_pds_test.c — M3.5 step 1: PDS drawindirect program generation test.
 *
 * Validates the PDS layer wiring before tackling real VDM ctx state + geom stream.
 * Run with: PVRGL_TEST_PDS=1 ./egl_clear_test (gated in egl_clear_test main)
 * Or build standalone: gcc -o pvrgl_pds_test pvrgl_pds_test.c -I... -lpvrgl
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "hwdef/rogue_hw_defs.h"
#include "hwdef/rogue_hw_utils.h"
#include "imagination/vulkan/pds/pvr_pds.h"
#include "imagination/vulkan/pvr_csb.h"
#include "imagination/vulkan/pvr_csb_enum_helpers.h"
#include "imagination/common/pvr_device_info.h"

/* Minimal device info for BXM-4-64 (B=6, V=52, N=0, C=0) */
static const struct pvr_device_info dev_info = {
   .ident = {
      .b = 6,
      .v = 52,
      .n = 0,
      .c = 0,
      .device_id = 0,
      .series_name = "BXM",
      .public_name = "BXM-4-64 MC1",
   },
   .features = {0},
   .enhancements = {0},
   .quirks = {0},
};

static int pds_test_run(void)
{
   struct pvr_pds_drawindirect_program prog = { 0 };
   uint32_t staging[128] = { 0 };
   uint32_t index_block_header = 0;

   /* Build INDEX_LIST0 header for triangle list, 3 vertices */
   struct ROGUE_VDMCTRL_INDEX_LIST0 list_hdr = { 0 };
   list_hdr.primitive_topology = ROGUE_VDMCTRL_PRIMITIVE_TOPOLOGY_TRI_LIST;
   list_hdr.index_count_present = true;
   list_hdr.index_instance_count_present = true;

   pvr_cmd_pack(VDMCTRL_INDEX_LIST0)(&index_block_header, &list_hdr);

   prog.index_list_addr_buffer = 0xDEADBEEF; /* dummy addr */
   prog.arg_buffer = 0xCAFEBABE;              /* dummy arg buffer addr */
   prog.index_buffer = PVR_DEV_ADDR_INVALID.addr;
   prog.index_block_header = index_block_header;
   prog.index_stride = 0; /* draw_arrays, no index buffer */
   prog.num_views = 1;
   prog.support_base_instance = true;
   prog.increment_draw_id = false;
   prog.count = 1;
   prog.stride = 0;

   /* SIZES pass */
   pvr_pds_generate_draw_arrays_indirect(&prog, NULL, PDS_GENERATE_SIZES, &dev_info);

   printf("PDS drawindirect SIZES:\n");
   printf("  code_size_aligned: %u dwords\n", prog.program.code_size_aligned);
   printf("  data_size_aligned: %u dwords\n", prog.program.data_size_aligned);
   printf("  temp_size_aligned: %u dwords\n", prog.program.temp_size_aligned);

   if (prog.program.code_size_aligned == 0 && prog.program.data_size_aligned == 0) {
      printf("FAIL: PDS generated zero-size program\n");
      return 1;
   }

   /* DATA pass - generate actual code + data into staging buffer */
   pvr_pds_generate_draw_arrays_indirect(&prog, staging, PDS_GENERATE_DATA_SEGMENT, &dev_info);

   /* Verify non-zero opcodes in code segment */
   bool has_opcodes = false;
   for (uint32_t i = 0; i < prog.program.code_size_aligned; i++) {
      if (staging[i] != 0) {
         has_opcodes = true;
         break;
      }
   }

   printf("PDS drawindirect DATA:\n");
   printf("  code segment (%u dwords): %s\n", prog.program.code_size_aligned,
          has_opcodes ? "NON-ZERO (PASS)" : "ALL ZERO (FAIL)");

   /* Print first few code dwords for inspection */
   printf("  First 8 code dwords: ");
   for (uint32_t i = 0; i < 8 && i < prog.program.code_size_aligned; i++) {
      printf("%08x ", staging[i]);
   }
   printf("\n");

   /* Check data segment */
   uint32_t *data_ptr = staging + prog.program.code_size_aligned;
   bool has_data = false;
   for (uint32_t i = 0; i < prog.program.data_size_aligned; i++) {
      if (data_ptr[i] != 0) {
         has_data = true;
         break;
      }
   }
   printf("  data segment (%u dwords): %s\n", prog.program.data_size_aligned,
          has_data ? "NON-ZERO (PASS)" : "ALL ZERO (FAIL)");

   if (!has_opcodes) {
      printf("FAIL: PDS code segment is all zeros\n");
      return 1;
   }

   printf("TEST RESULT PASS\n");
   return 0;
}

/* Exported entry point for dlsym from egl_clear_test */
int pvrgl_pds_test_main(void);

int pvrgl_pds_test_main(void)
{
   return pds_test_run();
}

/* Standalone main for direct execution */
int main(void)
{
   return pds_test_run();
}