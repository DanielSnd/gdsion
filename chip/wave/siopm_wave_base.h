/***************************************************/
/* Part of GDSiON software synthesizer             */
/* Copyright (c) 2024 Yuri Sizov and contributors  */
/* Provided under MIT                              */
/***************************************************/

#ifndef SIOPM_WAVE_BASE_H
#define SIOPM_WAVE_BASE_H

#include "core/object/ref_counted.h"
#include "servers/audio/audio_stream.h"
#include "core/templates/vector.h"
#include "core/variant/variant.h"
#include "../../sion_enums.h"
#include "core/io/marshalls.h"



class SiOPMWaveBase : public RefCounted {
	GDCLASS(SiOPMWaveBase, RefCounted)

	SiONModuleType _module_type = SiONModuleType::MODULE_MAX;

protected:
	static void _bind_methods() {}

	Vector<double> _extract_wave_data(const Ref<AudioStream> &p_stream, int *r_channel_count);

public:

	int64_t decode_s8(PackedByteArray *p_instance, int64_t p_offset);
	int64_t decode_s16(PackedByteArray *p_instance, int64_t p_offset);

	SiONModuleType get_module_type() const { return _module_type; }

	SiOPMWaveBase(SiONModuleType p_module_type = SiONModuleType::MODULE_MAX);
	~SiOPMWaveBase() {}
};

#endif // SIOPM_WAVE_BASE_H
