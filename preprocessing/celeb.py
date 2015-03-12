#!/usr/bin/env python
# Software License Agreement (BSD License)
#
# Copyright (c) 2012, Philipp Wagner
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above
#    copyright notice, this list of conditions and the following
#    disclaimer in the documentation and/or other materials provided
#    with the distribution.
#  * Neither the name of the author nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

import sys, math, Image

def Distance(p1,p2):
  dx = p2[0] - p1[0]
  dy = p2[1] - p1[1]
  return math.sqrt(dx*dx+dy*dy)

def ScaleRotateTranslate(image, angle, center = None, new_center = None, scale = None, resample=Image.BICUBIC):
  if (scale is None) and (center is None):
    return image.rotate(angle=angle, resample=resample)
  nx,ny = x,y = center
  sx=sy=1.0
  if new_center:
    (nx,ny) = new_center
  if scale:
    (sx,sy) = (scale, scale)
  cosine = math.cos(angle)
  sine = math.sin(angle)
  a = cosine/sx
  b = sine/sx
  c = x-nx*a-ny*b
  d = -sine/sy
  e = cosine/sy
  f = y-nx*d-ny*e
  return image.transform(image.size, Image.AFFINE, (a,b,c,d,e,f), resample=resample)

def CropFace(image, eye_left=(0,0), eye_right=(0,0), offset_pct=(0.2,0.2), dest_sz = (70,70)):
  # calculate offsets in original image
  offset_h = math.floor(float(offset_pct[0])*dest_sz[0])
  offset_v = math.floor(float(offset_pct[1])*dest_sz[1])
  # get the direction
  eye_direction = (eye_right[0] - eye_left[0], eye_right[1] - eye_left[1])
  # calc rotation angle in radians
  rotation = -math.atan2(float(eye_direction[1]),float(eye_direction[0]))
  # distance between them
  dist = Distance(eye_left, eye_right)
  # calculate the reference eye-width
  reference = dest_sz[0] - 2.0*offset_h
  # scale factor
  scale = float(dist)/float(reference)
  # rotate original around the left eye
  image = ScaleRotateTranslate(image, center=eye_left, angle=rotation)
  # crop the rotated image
  crop_xy = (eye_left[0] - scale*offset_h, eye_left[1] - scale*offset_v)
  crop_size = (dest_sz[0]*scale, dest_sz[1]*scale)
  image = image.crop((int(crop_xy[0]), int(crop_xy[1]), int(crop_xy[0]+crop_size[0]), int(crop_xy[1]+crop_size[1])))
  # resize it
  image = image.resize(dest_sz, Image.ANTIALIAS)
  return image

RAW_PATH = "../data/raw/"
CELEB_PATH = "../data/celeb/"

if __name__ == "__main__":
  image =  Image.open(RAW_PATH + "im1m.jpg")
  CropFace(image, eye_left=(342,662), eye_right=(616,670), offset_pct=(0.3,0.3), dest_sz=(92,112)).save(CELEB_PATH + "im1m.jpg")

  image =  Image.open(RAW_PATH + "im2m.jpg")
  CropFace(image, eye_left=(450,262), eye_right=(563,275), offset_pct=(0.3,0.3), dest_sz=(92,112)).save(CELEB_PATH + "im2m.jpg")

  image =  Image.open(RAW_PATH + "im3m.jpg")
  CropFace(image, eye_left=(735,798), eye_right=(1038,804), offset_pct=(0.3,0.3), dest_sz=(92,112)).save(CELEB_PATH + "im3m.jpg")

  image =  Image.open(RAW_PATH + "im4m.jpg")
  CropFace(image, eye_left=(312,376), eye_right=(460,373), offset_pct=(0.3,0.3), dest_sz=(92,112)).save(CELEB_PATH + "im4m.jpg")

  image =  Image.open(RAW_PATH + "im5m.jpg")
  CropFace(image, eye_left=(170,120), eye_right=(215,120), offset_pct=(0.3,0.3), dest_sz=(92,112)).save(CELEB_PATH + "im5m.jpg")

  image =  Image.open(RAW_PATH + "im1f.jpg")
  CropFace(image, eye_left=(463,359), eye_right=(601,360), offset_pct=(0.3,0.3), dest_sz=(92,112)).save(CELEB_PATH + "im1f.jpg")

  image =  Image.open(RAW_PATH + "im2f.jpg")
  CropFace(image, eye_left=(372,568), eye_right=(605,565), offset_pct=(0.3,0.3), dest_sz=(92,112)).save(CELEB_PATH + "im2f.jpg")

  image =  Image.open(RAW_PATH + "im3f.jpg")
  CropFace(image, eye_left=(426,400), eye_right=(583,396), offset_pct=(0.3,0.3), dest_sz=(92,112)).save(CELEB_PATH + "im3f.jpg")

  image =  Image.open(RAW_PATH + "im4f.jpg")
  CropFace(image, eye_left=(123,109), eye_right=(167,112), offset_pct=(0.3,0.3), dest_sz=(92,112)).save(CELEB_PATH + "im4f.jpg")

  image =  Image.open(RAW_PATH + "im5f.jpg")
  CropFace(image, eye_left=(197,208), eye_right=(258,209), offset_pct=(0.3,0.3), dest_sz=(92,112)).save(CELEB_PATH + "im5f.jpg")

  ###################################
  # Download links for images 
  ###################################
  # Download the images form the links and save them as indicated in 
  # the folder data/raw
  # Additionally, create folder data/celeb 
  # 
  # Males saved as (im#(number)m.jpg) : im1m.jpg -> im5m.jpg 
  # http://static4.wikia.nocookie.net/__cb20130808202627/marvelmovies/images/e/ee/Brad-Pitt.jpg
  # http://images2.fanpop.com/image/photos/9000000/Matt-Damon-matt-damon-9040366-1024-768.jpg
  # http://upload.wikimedia.org/wikipedia/commons/0/0d/Christian_Bale_2009.jpg
  # http://cdn.cnwimg.com/wp-content/uploads/2009/10/Tom-Hanks-768x1024.jpg
  # http://images.askmen.com/photos/ryan-reynolds/86365.jpg
  # 
  # Females saved as (im#(number)f.jpg): im1f.jpg -> im5f.jpg
  # http://www.interiordev.com/imagedir/jessica-beils-most-stunning-looks.jpg
  # http://celebritiesexercise.com/wp-content/uploads/2013/05/mila-kunis.jpg
  # http://ucesy-sk.happyhair.sk/celebrity_img/longoria2mj2509.jpg
  # http://fast.celebrityphoto.com/img/NatalieHall112711-SD21.JPG
  # http://img005.lazygirls.info/people/veronica_hamel/veronica_hamel_18_veronica_ca_1990_bKzbTVq.sized.jpg
