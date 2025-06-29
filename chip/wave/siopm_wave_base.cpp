/***************************************************/
/* Part of GDSiON software synthesizer             */
/* Copyright (c) 2024 Yuri Sizov and contributors  */
/* Provided under MIT                              */
/***************************************************/

#include "siopm_wave_base.h"

#include "scene/resources/audio_stream_wav.h"

SiOPMWaveBase::SiOPMWaveBase(SiONModuleType p_module_type) {
	_module_type = p_module_type;
}

int64_t SiOPMWaveBase::decode_s8(PackedByteArray *p_instance, int64_t p_offset) {
	uint64_t size = p_instance->size();
	ERR_FAIL_COND_V(p_offset < 0 || p_offset > int64_t(size) - 1, 0);
	const uint8_t *r = p_instance->ptr();
	return *((const int8_t *)&r[p_offset]);
}

int64_t SiOPMWaveBase::decode_s16(PackedByteArray *p_instance, int64_t p_offset) {
	uint64_t size = p_instance->size();
	ERR_FAIL_COND_V(p_offset < 0 || p_offset > (int64_t(size) - 2), 0);
	const uint8_t *r = p_instance->ptr();
	return (int16_t)decode_uint16(&r[p_offset]);
}

Vector<double> SiOPMWaveBase::_extract_wave_data(const Ref<AudioStream> &p_stream, int *r_channel_count) {
	if (p_stream.is_null()) {
		return Vector<double>();
	}

	Ref<AudioStreamWAV> wav_stream = p_stream;
	if (wav_stream.is_valid()) {
		AudioStreamWAV::Format data_format = wav_stream->get_format();
		if (data_format != AudioStreamWAV::FORMAT_8_BITS && data_format != AudioStreamWAV::FORMAT_16_BITS) {
			ERR_FAIL_V_MSG(Vector<double>(), vformat("SiOPMWaveBase: Unsupported WAV file format (%d).", data_format));
		}

		*r_channel_count = (wav_stream->is_stereo() ? 2 : 1);
		PackedByteArray wav_data = wav_stream->get_data();
		Vector<double> raw_data;

		int offset = 0;
		while (offset < wav_data.size()) {
			switch (data_format) {
				case AudioStreamWAV::FORMAT_8_BITS: {
					int value = decode_s8(&wav_data, offset);
					double sample = float(value) / 127.0; // Max int8.
					raw_data.push_back(sample);

					offset += 1;
				} break;

				case AudioStreamWAV::FORMAT_16_BITS: {
					int value = decode_s16(&wav_data, offset);
					double sample = float(value) / 32767.0; // Max int16.
					raw_data.push_back(sample);

					offset += 2;
				} break;

				default:
					offset += 1;
					break;
			}
		}

		return raw_data;
	}

	ERR_FAIL_V_MSG(Vector<double>(), "SiOPMWaveBase: Unsupported audio stream format.");
}
