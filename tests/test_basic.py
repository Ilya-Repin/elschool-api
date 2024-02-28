import pytest

from testsuite.databases import pgsql

from testsuite import utils


# Start the tests via `make test-debug` or `make test-release`


@pytest.mark.pgsql('db_1', files=['initial_data.sql'])
async def test_db_delete_initial_data(service_client):
    response = await service_client.delete(
        '/v1/users',
        params={'id': 'e5e79b0d1e2c49f097db4930c9ea8c43'},
    )
    assert response.status == 200
    assert response.text == 'Deleted!'


@pytest.mark.parametrize(
    "login, password, status",
    [
        pytest.param(
            'test_user',
            'test_password',
            200,
        ),
    ]
)
async def test_add_user(service_client, mockserver, login, password, status):
    @mockserver.handler('elschool.ru/logon/index')
    def _mock_logon_index_post(request):
        assert request.method == 'POST'

        # if request.args['login'] == 'test_user' and request.args['password'] == 'test_password':
        return mockserver.make_response('privateoffice', content_type='text/html', status=302)
        # else:
        #    return mockserver.make_response('', content_type='text/html', status=302)

    response = await service_client.post(
        '/v1/users',
        data={'login': login, 'password': password},
    )

    if status == 200:
        assert response.status == 200
        assert response.text != ''
    elif status == 500:
        assert response.status == 500
        assert response.text == 'Failed to add user!'
