//************************************************************
// SimpleSoundPlayer.hxx
//
// Created on Wed Sep 12 17:52:56 2012 by Jan Comans
//
// Copyright 2012 Jan Comans -- j.comans@tudelft.nl
//
// License TBD
//************************************************************
#ifndef _SIMPLESOUNDPLAYER_H_
#define _SIMPLESOUNDPLAYER_H_

#include <vector>
#include <sys/types.h>

#include <AL/alut.h>

// A simple class to play wav files
class SimpleSoundPlayer
{
public:
  // No arguments needed, will open the default device
  SimpleSoundPlayer();
  ~SimpleSoundPlayer();

public:
  // Add a new wavefile to the list that can be played.
  // Samples are in the list in the order you put them in
  size_t addSoundFile(const char* wav_filename);

  // Play a sample from the list, samples are in the
  // order they where put in by addSoundFile. Indices start
  // at 0
  void playSound(size_t index) const;

  // Stop a sample that is playing
  void stopSound(size_t index) const;

  // Check if a sound is playing
  bool isSoundPlaying(size_t index) const;

  // Stop all samples at once
  void stopAllSound() const;

  //Enable or disable looping for a sample
  void setLoop(size_t index, bool enabled) const;

  // Set pitch for a sample
  void setPitch(size_t index, float pitch = 1.0f ) const;

  // Set gain for a sample
  void setGain(size_t index, float gain = 1.0f ) const;
  
  inline int num_samples() {return _sound_sources.size();}

private:
  typedef std::vector<ALuint> SoundSources;
  SoundSources _sound_sources;
};

#endif /* _SIMPLESOUNDPLAYER_H_ */
