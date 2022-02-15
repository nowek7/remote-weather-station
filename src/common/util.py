import const
import externals.rsa as rsa

from ubinascii import b2a_base64
import ujson
import utime

def get_config() -> dict:
    config = {}
    with open('./generated/config.json', 'r') as json_file:
        config = ujson.load(json_file)
    return config

def b42_urlsafe_encode(payload):
    return string.translate(b2a_base64(payload)[:-1].decode('utf-8'),{ ord('+'):'-', ord('/'):'_' })

def create_jwt(project_id, private_key, algorithm, token_ttl):
    print("Creating JWT...")
    private_key = rsa.PrivateKey(*private_key)

    claims = {
        # The time that the token was issued at
        'iat': utime.time() + const.EPOCH_OFFSET,
        # The time the token expires.
        'exp': utime.time() + const.EPOCH_OFFSET + token_ttl,
        # The audience field should always be set to the GCP project id.
        'aud': project_id
    }

    #This only supports RS256 at this time.
    header = { 'alg': algorithm, 'typ': 'JWT' }
    content = b42_urlsafe_encode(ujson.dumps(header).encode('utf-8'))
    content = content + '.' + b42_urlsafe_encode(ujson.dumps(claims).encode('utf-8'))
    signature = b42_urlsafe_encode(rsa.sign(content, private_key,'SHA-256'))

    # signed JWT
    return f"{content}.{signature}"