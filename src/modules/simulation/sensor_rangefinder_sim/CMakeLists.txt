px4_add_module(
	MODULE modules__simulation__sensor_rangefinder_sim
	MAIN sensor_rangefinder_sim
	COMPILE_FLAGS
	SRCS
		SensorRangefinderSim.cpp
		SensorRangefinderSim.hpp
	DEPENDS
		px4_work_queue
	)