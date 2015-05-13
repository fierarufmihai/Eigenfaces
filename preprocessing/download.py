#!/usr/bin/env python
import requests



links = {"im1m": "http://static4.wikia.nocookie.net/__cb20130808202627/marvelmovies/images/e/ee/Brad-Pitt.jpg", \
 "im2m": "http://images2.fanpop.com/image/photos/9000000/Matt-Damon-matt-damon-9040366-1024-768.jpg", \
 "im3m": "http://upload.wikimedia.org/wikipedia/commons/0/0d/Christian_Bale_2009.jpg", \
 "im4m": "http://cdn.cnwimg.com/wp-content/uploads/2009/10/Tom-Hanks-768x1024.jpg", \
 "im5m": "http://images.askmen.com/photos/ryan-reynolds/86365.jpg", \
 "im1f": "http://www.interiordev.com/imagedir/jessica-beils-most-stunning-looks.jpg", \
 "im2f": "http://celebritiesexercise.com/wp-content/uploads/2013/05/mila-kunis.jpg", \
 "im3f": "http://ucesy-sk.happyhair.sk/celebrity_img/longoria2mj2509.jpg", \
 "im4f": "http://fast.celebrityphoto.com/img/NatalieHall112711-SD21.JPG", \
 "im5f": "http://img005.lazygirls.info/people/veronica_hamel/veronica_hamel_18_veronica_ca_1990_bKzbTVq.sized.jpg"}

for im_name in links:
	f = open("data/raw/" + im_name + ".jpg",'wb')
	f.write(requests.get(links[im_name]).content)
	f.close()