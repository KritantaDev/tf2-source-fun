	// Count kills from powerup carriers to detect imbalances
	if ( IFuncPowerupVolumeAutoList::AutoList().Count() != 0 ) // If there are no func_powerupvolumes in the map, there's no point in checking for imbalances
	{
		if ( pTFPlayerScorer && pTFPlayerScorer != pTFPlayerVictim && pTFPlayerScorer->m_Shared.IsCarryingRune() && !pTFPlayerScorer->m_Shared.InCond( TF_COND_RUNE_IMBALANCE ) )
		{
			if ( !m_bPowerupImbalanceMeasuresRunning && !PowerupModeFlagStandoffActive() ) // Only count if imbalance measures aren't running and there is no flag standoff 
			{
				if ( pTFPlayerScorer->GetTeamNumber() == TF_TEAM_BLUE )
				{
					m_nPowerupKillsBlueTeam++;		// Blue team score increases if a powered up blue player makes a kill
				}
				else if ( pTFPlayerScorer->GetTeamNumber() == TF_TEAM_RED )
				{
					m_nPowerupKillsRedTeam++;
				}

				int nBlueAdvantage = m_nPowerupKillsBlueTeam - m_nPowerupKillsRedTeam;		// How far ahead is this team?
//				Msg( "\nnBlueAdvantage = %d\n", nBlueAdvantage );
				int nRedAdvantage = m_nPowerupKillsRedTeam - m_nPowerupKillsBlueTeam;
//				Msg( "nRedAdvantage = %d\n\n", nRedAdvantage );

				if ( nRedAdvantage >= tf_powerup_mode_imbalance_delta.GetInt() ) // Delta is 24
				{
					PowerupTeamImbalance( TF_TEAM_BLUE );		// Fire the output to map logic
				}
				else if ( nBlueAdvantage >= tf_powerup_mode_imbalance_delta.GetInt() )
				{
					PowerupTeamImbalance( TF_TEAM_RED );
				}
			}
		}
	}
