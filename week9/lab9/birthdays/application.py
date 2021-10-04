import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

message = None

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)
        return redirect("/")

    else:
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)


@app.route("/<id>", methods=["DELETE", "PATCH"])
def remove(id):
    if request.method == "DELETE":
        if db.execute("SELECT * FROM birthdays WHERE id = ?", id):
            db.execute("DELETE FROM birthdays WHERE id = ?", id)
            data = { "data": "birthday deleted successfully" }
            return data, 204

        data = { "error": "birthday already deleted from server" }
        return data, 404

    elif request.method == "PATCH":
        data = request.json
        b = db.execute("SELECT * FROM birthdays WHERE id = ?", id)

        if b:
            name = data["name"] or b["name"]
            month = data["month"] or b["month"]
            day = data["day"] or b["day"]
            db.execute("UPDATE birthdays SET name = ?, month = ?, day = ? WHERE id = ?", name, month, day, id)
            return '', 204

        return '', 404
