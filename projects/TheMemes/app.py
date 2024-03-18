#!/bin/python

from flask import Flask, render_template, request
import requests
import json

app = Flask(__name__)

def get_meme():
	url = "https://meme-api.com/gimme"
	response = json.loads(requests.request("GET", url).text)
	meme_large = response["preview"][-2]
	return meme_large

@app.route("/update_name", methods=["POST"])
def set_title():
    username = request.form["username"]
    if not username:
        username = "Guest"
    meme_pic = get_meme()
    return render_template("meme_index.html", meme_pic=meme_pic, user=username)

@app.route("/", methods=["GET"])
def index():
	meme_pic = get_meme()
	return render_template("meme_index.html", meme_pic=meme_pic, user="Guest")

app.run(host="0.0.0.0", port=80)

