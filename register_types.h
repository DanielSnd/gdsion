/***************************************************/
/* Part of GDSiON software synthesizer             */
/* Copyright (c) 2024 Yuri Sizov and contributors  */
/* Provided under MIT                              */
/***************************************************/

#ifndef SION_REGISTER_TYPES_H
#define SION_REGISTER_TYPES_H

#include "core/object/class_db.h"
#include "modules/register_module_types.h"


void initialize_gdsion_module(ModuleInitializationLevel p_level);
void uninitialize_gdsion_module(ModuleInitializationLevel p_level);

#endif // SION_REGISTER_TYPES_H
