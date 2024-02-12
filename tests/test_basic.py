import pytest

from testsuite.databases import pgsql


# Start the tests via `make test-debug` or `make test-release`


@pytest.mark.pgsql('db_1', files=['initial_data.sql'])
async def test_db_delete_initial_data(service_client):
    response = await service_client.delete(
        '/v1/users',
        params={'id': 'e5e79b0d1e2c49f097db4930c9ea8c43'},
    )
    assert response.status == 200
    assert response.text == 'Deleted!'
