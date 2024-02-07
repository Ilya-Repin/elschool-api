import pytest

from testsuite.databases import pgsql


async def test_first_time_users(service_client):
    assert 200 == 200


async def test_db_updates(service_client):
    assert 200 == 200


@pytest.mark.pgsql('db_1', files=['initial_data.sql'])
async def test_db_initial_data(service_client):
    assert 200 == 200
