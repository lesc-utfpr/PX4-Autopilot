#include "SensorRangefinderSim.hpp"

#include <px4_platform_common/getopt.h>
#include <px4_platform_common/log.h>

SensorRangefinderSim::SensorRangefinderSim() :
	ModuleParams(nullptr),
	ScheduledWorkItem(MODULE_NAME, px4::wq_configurations::hp_default)
{
}

SensorRangefinderSim::~SensorRangefinderSim()
{
	perf_free(_loop_perf);
}

bool SensorRangefinderSim::init()
{
	// Run at 50 Hz — matches a typical rangefinder update rate
	ScheduleOnInterval(20_ms);
	return true;
}

void SensorRangefinderSim::Run()
{
	if (should_exit()) {
		ScheduleClear();
		exit_and_cleanup();
		return;
	}

	perf_begin(_loop_perf);

	// Update parameters if needed
	if (_parameter_update_sub.updated()) {
		parameter_update_s param_update;
		_parameter_update_sub.copy(&param_update);
		updateParams();
	}

	// Get ground-truth local position from gz_bridge
	vehicle_local_position_s lpos{};

	if (_vehicle_local_position_sub.update(&lpos)) {
		// lpos.z is NED: negative = above ground. Distance to ground = -lpos.z
		// (assuming flat ground at z=0, which is fine for SITL)
		float dist = -lpos.z;

		const float min_dist = _sim_rng_min.get();
		const float max_dist = _sim_rng_max.get();

		// Clamp to sensor limits
		if (dist < min_dist) { dist = min_dist; }
		if (dist > max_dist) { dist = max_dist; }

		distance_sensor_s report{};
		report.timestamp        = hrt_absolute_time();
		report.min_distance     = min_dist;
		report.max_distance     = max_dist;
		report.current_distance = dist;
		report.variance         = 0.01f;       // 10 cm std dev
		report.signal_quality   = 100;
		report.type             = distance_sensor_s::MAV_DISTANCE_SENSOR_LASER;
		report.orientation      = distance_sensor_s::ROTATION_DOWNWARD_FACING;
		report.h_fov            = 0.05f;       // ~3 deg, typical 1D lidar
		report.v_fov            = 0.05f;
		report.device_id        = 1311244;     // arbitrary stable ID

		_distance_sensor_pub.publish(report);
	}

	perf_end(_loop_perf);
}

int SensorRangefinderSim::task_spawn(int argc, char *argv[])
{
	SensorRangefinderSim *instance = new SensorRangefinderSim();

	if (instance) {
		_object.store(instance);
		_task_id = task_id_is_work_queue;

		if (instance->init()) {
			return PX4_OK;
		}

	} else {
		PX4_ERR("alloc failed");
	}

	delete instance;
	_object.store(nullptr);
	_task_id = -1;

	return PX4_ERROR;
}

int SensorRangefinderSim::custom_command(int argc, char *argv[])
{
	return print_usage("unknown command");
}

int SensorRangefinderSim::print_usage(const char *reason)
{
	if (reason) {
		PX4_WARN("%s\n", reason);
	}

	PRINT_MODULE_DESCRIPTION(
		R"DESCR_STR(
### Description
Simulated rangefinder (distance sensor) for Gazebo SITL.
Reads vehicle_local_position_groundtruth and publishes distance_sensor uORB.
)DESCR_STR");

	PRINT_MODULE_USAGE_NAME("sensor_rangefinder_sim", "system");
	PRINT_MODULE_USAGE_COMMAND("start");
	PRINT_MODULE_USAGE_DEFAULT_COMMANDS();

	return 0;
}

extern "C" __attribute__((visibility("default"))) int sensor_rangefinder_sim_main(int argc, char *argv[])
{
	return SensorRangefinderSim::main(argc, argv);
}