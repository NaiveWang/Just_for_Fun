from flask import Flask, render_template, jsonify, request, send_from_directory
from flask import make_response


app = Flask(__name__)


@app.route("/")
def main_page():
    print(request.method)
    return render_template('main.html')
@app.route("/flashcard")
def flashcard_page():
    print(request.method)
    return render_template('flashcard.html')
