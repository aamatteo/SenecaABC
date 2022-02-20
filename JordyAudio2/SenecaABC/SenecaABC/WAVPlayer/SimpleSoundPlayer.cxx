//************************************************************
// SimpleSoundPlayer.cxx
//
// Created on Wed Sep 12 18:03:30 2012 by Jan Comans
//
// Copyright 2012 Jan Comans -- j.comans@tudelft.nl
//
// License TBD
//************************************************************
#include "SimpleSoundPlayer.hxx"

#include <boost/foreach.hpp>

SimpleSoundPlayer::SimpleSoundPlayer()
{
  // This is a horible way of doing thing, but for now its ok
  int dummyargc = 1;
  const char* dummyargv = "dummy";
  if( alutInit(&dummyargc, (char**)&dummyargv) == AL_FALSE)
    throw "Unable to initialize alut";
}

SimpleSoundPlayer::~SimpleSoundPlayer()
{
  alutExit();
}

size_t SimpleSoundPlayer::addSoundFile(const char* wav_filename)
{
  ALuint buffer = alutCreateBufferFromFile( wav_filename );

  if(buffer == AL_NONE) throw "Unable to open file";

  // Request a new source handle
  ALuint source;
  alGenSources(1,&source);

  // Couple the source to the buffer
  alSourcei(source, AL_BUFFER, buffer);

  // Keep track of this sample in our vector
  _sound_sources.push_back( source );

  return _sound_sources.size() - 1;
}

void SimpleSoundPlayer::playSound(size_t index) const
{
  alSourcePlay( _sound_sources.at(index) );
}

void SimpleSoundPlayer::stopSound(size_t index) const
{
  alSourceStop( _sound_sources.at(index) );
}

bool SimpleSoundPlayer::isSoundPlaying(size_t index) const
{
  ALenum state;

  alGetSourcei( _sound_sources.at(index), AL_SOURCE_STATE, &state );

  return ( state == AL_PLAYING );
}

void SimpleSoundPlayer::stopAllSound() const
{
  BOOST_FOREACH( SoundSources::value_type source, _sound_sources)
    alSourceStop( source );
}

void SimpleSoundPlayer::setLoop(size_t index, bool enabled) const
{
  alSourcei( _sound_sources.at(index), AL_LOOPING, enabled? AL_TRUE:AL_FALSE );
}

void SimpleSoundPlayer::setPitch(size_t index, float pitch) const
{
  alSourcef( _sound_sources.at(index), AL_PITCH, pitch );
}

// PETER
void SimpleSoundPlayer::setGain(size_t index, float gain) const
{
  alSourcef( _sound_sources.at(index), AL_GAIN, gain );
}

