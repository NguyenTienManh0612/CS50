from flask import Flask, redirect, render_template, request

app = Flask(__name__)

SPORTS = [
    "Basketball",
    "Soccer",
    "Table tennis"
]

REGISTRANTS = {}

REGISTRANTS_LIST = []
@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

# @app.route("/register", methods=["POST"])
# def register():
#     if not request.form.get("name"):
#         return "failure"
#     return "success"

# @app.route("/register", methods=["POST"])
# def register():

#     # Validate submission
#     if not request.form.get("name"): #or request.form.get("sport") not in SPORTS:
#         return render_template("failure.html")
#     for sport in request.form.getlist("sport"):
#         if sport not in SPORTS:
#             return render_template("failure.html")
#     # Confirm registration
#     return render_template("success.html")

@app.route("/register", methods=["POST"])
def register():
    name = request.form.get("name")
    if not name:
        return render_template("error.html", message = "Missing name")
    REGISTRANTS[name] = ""
    # sport = request.form.get("sport")
    if not request.form.get("sport"):
        return render_template("error.html", message = "Missing sport")
    for sport in request.form.getlist("sport"):
        if sport not in SPORTS:
            return render_template("error.html", message = "Invalid sport")
        else:
            REGISTRANTS[name] += sport
        REGISTRANTS[name] += ", "

    return redirect("/registrants")

@app.route("/registrants")
def registrants():
    return render_template("registrants.html", registrants=REGISTRANTS)
