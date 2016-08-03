/**\file */
#ifndef SLIC_DECLARATIONS_monprox2_H
#define SLIC_DECLARATIONS_monprox2_H
#include "MaxSLiCInterface.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int monprox2_has_errors(void);
const char* monprox2_get_errors(void);


/*----------------------------------------------------------------------------*/
/*---------------------------- Interface default -----------------------------*/
/*----------------------------------------------------------------------------*/



/**
 * \brief Basic static function for the interface 'default'.
 * 
 * \param [in] param_N Interface Parameter "N".: Number of data items to process
 * \param [in] inscalar_monprox2Kernel_a1 Input scalar parameter "monprox2Kernel.a1".
 * \param [in] inscalar_monprox2Kernel_a2 Input scalar parameter "monprox2Kernel.a2".
 * \param [in] instream_b1 The stream should be of size (param_N * 4) bytes.
 * \param [in] instream_b2 The stream should be of size (param_N * 4) bytes.
 * \param [out] outstream_x1 The stream should be of size (param_N * 4) bytes.
 * \param [out] outstream_x2 The stream should be of size (param_N * 4) bytes.
 * \param [out] outstream_y1 The stream should be of size (param_N * 4) bytes.
 * \param [out] outstream_y2 The stream should be of size (param_N * 4) bytes.
 */
void monprox2(
	int32_t param_N,
	uint64_t inscalar_monprox2Kernel_a1,
	uint64_t inscalar_monprox2Kernel_a2,
	const uint32_t *instream_b1,
	const uint32_t *instream_b2,
	uint32_t *outstream_x1,
	uint32_t *outstream_x2,
	uint32_t *outstream_y1,
	uint32_t *outstream_y2);

/**
 * \brief Basic static non-blocking function for the interface 'default'.
 * 
 * Schedule to run on an engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 * 
 * 
 * \param [in] param_N Interface Parameter "N".: Number of data items to process
 * \param [in] inscalar_monprox2Kernel_a1 Input scalar parameter "monprox2Kernel.a1".
 * \param [in] inscalar_monprox2Kernel_a2 Input scalar parameter "monprox2Kernel.a2".
 * \param [in] instream_b1 The stream should be of size (param_N * 4) bytes.
 * \param [in] instream_b2 The stream should be of size (param_N * 4) bytes.
 * \param [out] outstream_x1 The stream should be of size (param_N * 4) bytes.
 * \param [out] outstream_x2 The stream should be of size (param_N * 4) bytes.
 * \param [out] outstream_y1 The stream should be of size (param_N * 4) bytes.
 * \param [out] outstream_y2 The stream should be of size (param_N * 4) bytes.
 * \return A handle on the execution status, or NULL in case of error.
 */
max_run_t *monprox2_nonblock(
	int32_t param_N,
	uint64_t inscalar_monprox2Kernel_a1,
	uint64_t inscalar_monprox2Kernel_a2,
	const uint32_t *instream_b1,
	const uint32_t *instream_b2,
	uint32_t *outstream_x1,
	uint32_t *outstream_x2,
	uint32_t *outstream_y1,
	uint32_t *outstream_y2);

/**
 * \brief Advanced static interface, structure for the engine interface 'default'
 * 
 */
typedef struct { 
	int32_t param_N; /**<  [in] Interface Parameter "N".: Number of data items to process */
	uint64_t inscalar_monprox2Kernel_a1; /**<  [in] Input scalar parameter "monprox2Kernel.a1". */
	uint64_t inscalar_monprox2Kernel_a2; /**<  [in] Input scalar parameter "monprox2Kernel.a2". */
	const uint32_t *instream_b1; /**<  [in] The stream should be of size (param_N * 4) bytes. */
	const uint32_t *instream_b2; /**<  [in] The stream should be of size (param_N * 4) bytes. */
	uint32_t *outstream_x1; /**<  [out] The stream should be of size (param_N * 4) bytes. */
	uint32_t *outstream_x2; /**<  [out] The stream should be of size (param_N * 4) bytes. */
	uint32_t *outstream_y1; /**<  [out] The stream should be of size (param_N * 4) bytes. */
	uint32_t *outstream_y2; /**<  [out] The stream should be of size (param_N * 4) bytes. */
} monprox2_actions_t;

/**
 * \brief Advanced static function for the interface 'default'.
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in,out] interface_actions Actions to be executed.
 */
void monprox2_run(
	max_engine_t *engine,
	monprox2_actions_t *interface_actions);

/**
 * \brief Advanced static non-blocking function for the interface 'default'.
 *
 * Schedule the actions to run on the engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in] interface_actions Actions to be executed.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *monprox2_run_nonblock(
	max_engine_t *engine,
	monprox2_actions_t *interface_actions);

/**
 * \brief Group run advanced static function for the interface 'default'.
 * 
 * \param [in] group Group to use.
 * \param [in,out] interface_actions Actions to run.
 *
 * Run the actions on the first device available in the group.
 */
void monprox2_run_group(max_group_t *group, monprox2_actions_t *interface_actions);

/**
 * \brief Group run advanced static non-blocking function for the interface 'default'.
 * 
 *
 * Schedule the actions to run on the first device available in the group and return immediately.
 * The status of the run must be checked with ::max_wait. 
 * Note that use of ::max_nowait is prohibited with non-blocking running on groups:
 * see the ::max_run_group_nonblock documentation for more explanation.
 *
 * \param [in] group Group to use.
 * \param [in] interface_actions Actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *monprox2_run_group_nonblock(max_group_t *group, monprox2_actions_t *interface_actions);

/**
 * \brief Array run advanced static function for the interface 'default'.
 * 
 * \param [in] engarray The array of devices to use.
 * \param [in,out] interface_actions The array of actions to run.
 *
 * Run the array of actions on the array of engines.  The length of interface_actions
 * must match the size of engarray.
 */
void monprox2_run_array(max_engarray_t *engarray, monprox2_actions_t *interface_actions[]);

/**
 * \brief Array run advanced static non-blocking function for the interface 'default'.
 * 
 *
 * Schedule to run the array of actions on the array of engines, and return immediately.
 * The length of interface_actions must match the size of engarray.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * \param [in] engarray The array of devices to use.
 * \param [in] interface_actions The array of actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *monprox2_run_array_nonblock(max_engarray_t *engarray, monprox2_actions_t *interface_actions[]);

/**
 * \brief Converts a static-interface action struct into a dynamic-interface max_actions_t struct.
 *
 * Note that this is an internal utility function used by other functions in the static interface.
 *
 * \param [in] maxfile The maxfile to use.
 * \param [in] interface_actions The interface-specific actions to run.
 * \return The dynamic-interface actions to run, or NULL in case of error.
 */
max_actions_t* monprox2_convert(max_file_t *maxfile, monprox2_actions_t *interface_actions);

/**
 * \brief Initialise a maxfile.
 */
max_file_t* monprox2_init(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* SLIC_DECLARATIONS_monprox2_H */

