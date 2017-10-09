#!flask/bin/python
from flask import Flask, jsonify, abort, request, make_response, url_for
app = Flask(__name__)

@app.errorhandler(400)
def not_found(error):
    return make_response(jsonify( { 'error': 'Bad request' } ), 400)

@app.errorhandler(404)
def not_found(error):
    return make_response(jsonify( { 'error': 'Not found' } ), 404)


instructions= [
    {
        'direction': 'NN',
    },
]

@app.route('/direction', methods=['GET'])
def get_tasks():
    return jsonify({'direction': instructions})


@app.route('/new_direction', methods = ['POST'])
def find_directions():

        if not request.json:
                abort(400)
        else:
                return jsonify({'direction':instructions})
                app.logger.debug("JSON received...")
                app.logger.debug(request.json)

if __name__ == '__main__':
    app.run(host='0.0.0.0',debug=True)
